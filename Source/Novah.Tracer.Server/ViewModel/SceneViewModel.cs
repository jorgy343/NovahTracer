﻿using System.IO;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Microsoft.Win32;

namespace Novah.Tracer.Server.ViewModel
{
    public class SceneViewModel : ViewModelBase
    {
        public SceneViewModel(string sceneXmlFilePath, int width, int height, int chunkCount)
            : base("Scene")
        {
            CreateSceneCommand = new RelayCommand(SaveToFile);

            Scene = new Scene(File.ReadAllText(sceneXmlFilePath), width, height, chunkCount);
            Bitmap = new WriteableBitmap(width, height, 96, 96, PixelFormats.Bgr32, null);
        }

        public void SaveToFile(object parameter)
        {
            lock (Bitmap)
            {
                var saveFileDialog = new SaveFileDialog();
                if (saveFileDialog.ShowDialog() ?? false)
                {
                    using (var file = new FileStream(saveFileDialog.FileName, FileMode.Create))
                    {
                        var encoder = new PngBitmapEncoder();
                        encoder.Frames.Add(BitmapFrame.Create(Bitmap));
                        encoder.Save(file);

                        file.Close();
                    }
                }
            }
        }

        public async void UpdateChunk(Chunk chunk, byte[] colorData)
        {
            await Application.Current.Dispatcher.InvokeAsync(() =>
            {
                using (var memoryStream = new MemoryStream(colorData))
                using (var binaryReader = new BinaryReader(memoryStream))
                {
                    lock (Bitmap)
                    {
                        Bitmap.Lock();

                        var backbuffer = Bitmap.BackBuffer;
                        var stride = Bitmap.BackBufferStride;

                        unsafe
                        {
                            for (var y = chunk.StartY; y < chunk.StartY + chunk.Height; ++y)
                            {
                                for (var x = 0; x < chunk.Width; ++x)
                                {
                                    var writeAddress = backbuffer + x * 4 + y * stride;
                                    int color = binaryReader.ReadInt32();
                                    *((int*)writeAddress) = color;
                                }
                            }
                        }

                        Bitmap.AddDirtyRect(new Int32Rect(0, chunk.StartY, chunk.Width, chunk.Height));
                        Bitmap.Unlock();
                    }
                }
            });
        }

        public Scene Scene { get; }
        public WriteableBitmap Bitmap { get; }

        public RelayCommand CreateSceneCommand { get; }
    }
}