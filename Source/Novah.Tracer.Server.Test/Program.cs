using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using static System.Console;

namespace Novah.Tracer.Server.Test
{
    public class Program
    {
        public static void Main(string[] args)
        {
            var client = new TcpClient();
            client.Connect(IPAddress.Loopback, 54000);

            using (var networkStream = client.GetStream())
            {
                for (var i = 0; i < 5; i++)
                    HandleChunk(networkStream);
            }

            ReadLine();
            client.Close();
        }

        public static void HandleChunk(NetworkStream networkStream)
        {
            using (var binaryWriter = new BinaryWriter(networkStream, Encoding.ASCII, true))
            using (var binaryReader = new BinaryReader(networkStream, Encoding.ASCII, true))
            {
                // Request a chunk.
                binaryWriter.Write(1);
                binaryWriter.Write(0);

                networkStream.Flush();

                // Read the chunk sent message.
                var messageType = binaryReader.ReadInt32();
                var messageSize = binaryReader.ReadInt32();

                var sceneId = binaryReader.ReadInt64();
                var chunkId = binaryReader.ReadInt64();

                var startY = binaryReader.ReadInt32();
                var width = binaryReader.ReadInt32();
                var height = binaryReader.ReadInt32();

                var messageData = binaryReader.ReadBytes(messageSize - sizeof(long) * 2 - sizeof(int) * 3);
                var messageDataText = Encoding.ASCII.GetString(messageData);

                WriteLine(messageType);
                WriteLine(messageSize);
                WriteLine(sceneId);
                WriteLine(chunkId);
                WriteLine(messageDataText);

                // Send back some chunk data.
                binaryWriter.Write(3);
                binaryWriter.Write(sizeof(long) * 2 + width * height * 4);

                binaryWriter.Write(sceneId);
                binaryWriter.Write(chunkId);

                var colorData = new byte[width * height * 4];
                new Random().NextBytes(colorData);

                binaryWriter.Write(colorData);
                binaryWriter.Flush();
            }
        }
    }
}