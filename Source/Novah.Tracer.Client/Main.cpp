#include <SDKDDKVer.h>
#include <ppl.h>
#include <ppltasks.h>

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <tuple>
#include <thread>
#include <sstream>

#include <winsock2.h>
#include <ws2tcpip.h>

#include "NovahTracerEngine.h"

#include "Console.h"
#include "Network.h"

enum class WorkerStatus
{
    RequestedChunk,
    ProcessingChunk,
    ChunkProcessedAndRequestingChunk
};

class ChunkData
{
public:
    int SceneId, ChunkId, Width, Height, ChunkHeight, StartY;
    const char* SceneXml;
};

class WorkerThreadState
{
public:
    concurrency::task<void> Task;
    SRWLOCK Lock;
    CONDITION_VARIABLE ConditionVariable;
    ChunkData Chunk;
    WorkerStatus Status;

    WorkerThreadState()
        : Status(WorkerStatus::RequestedChunk)
    {

    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    // Start of normal program flow.
    unsigned int totalWorkingThreads = max(std::thread::hardware_concurrency() - 1, 1);
    //totalWorkingThreads = 1;

    Console console(totalWorkingThreads + 1);

    //console.UpdateStatus(0, "Connecting to server...");
    //Network network("104.159.179.98", "54000");

    //auto workerThreadStates = new WorkerThreadState[totalWorkingThreads];
    //console.UpdateStatus(0, "Spinning up 1 support thread.");

    //auto supportTask = concurrency::create_task([&console, &network, totalWorkingThreads, &workerThreadStates]
    //{
    //    while (true)
    //    {
    //        if (network.IsMessageReady())
    //        {
    //            auto message = network.GetMessage();
    //            auto messageData = message.get();

    //            int sceneId = *(int*)(messageData + 0);
    //            int chunkId = *(int*)(messageData + 4);

    //            int width = *(int*)(messageData + 8);
    //            int height = *(int*)(messageData + 12);
    //            int chunkHeight = *(int*)(messageData + 16);
    //            int startY = *(int*)(messageData + 20);

    //            const char* sceneXml = messageData + 24;

    //            console.AddHistory(0, "Chunk Received. Scene Id: ", sceneId, " Chunk Id: ", chunkId);
    //            for (int i = 0; i < totalWorkingThreads; i++)
    //            {
    //                if (workerThreadStates[i].Status == WorkerStatus::RequestedChunk || workerThreadStates[i].Status == WorkerStatus::ChunkProcessedAndRequestingChunk)
    //                {
    //                    workerThreadStates[i].Chunk.SceneId = sceneId;
    //                    workerThreadStates[i].Chunk.ChunkId = chunkId;
    //                    workerThreadStates[i].Chunk.Width = width;
    //                    workerThreadStates[i].Chunk.Height = height;
    //                    workerThreadStates[i].Chunk.ChunkHeight = chunkHeight;
    //                    workerThreadStates[i].Chunk.StartY = startY;
    //                    workerThreadStates[i].Chunk.SceneXml = sceneXml;

    //                    workerThreadStates[i].Status = WorkerStatus::ProcessingChunk;
    //                    WakeConditionVariable(&workerThreadStates[i].ConditionVariable);

    //                    break;
    //                }
    //            }
    //        }

    //        network.Read();
    //    }
    //});

    //console.UpdateStatus(0, "Spinning up ", totalWorkingThreads, " worker thread", totalWorkingThreads == 1 ? "" : "s", ".");

    std::vector<concurrency::task<void>> tasks;
    for (int i = 0; i < totalWorkingThreads; i++)
    {
        //InitializeSRWLock(&workerThreadStates[i].Lock);
        //InitializeConditionVariable(&workerThreadStates[i].ConditionVariable);
        //workerThreadStates[i].Status = WorkerStatus::RequestedChunk;

        //WorkerThreadState* workerThreadState = &workerThreadStates[i];
        //workerThreadState->Task = concurrency::create_task([i, &console, &network, workerThreadState]
        auto task = concurrency::create_task([i, &console]
        {
            auto network = new Network("127.0.0.1", "54000");

            int threadIndex = i;
            //console.UpdateStatus(threadIndex + 1, "Thread ", threadIndex, ": Created.");

            //SetThreadAffinityMask(GetCurrentThread(), 1 << threadIndex);
            while (true)
            {
                console.UpdateStatus(i, "Requesting chunk...");
                network->SendChunkRequestedMessage();

                auto message = network->GetMessage();
                auto messageData = message.get();

                int sceneId = *(int*)(messageData + 0);
                int chunkId = *(int*)(messageData + 4);

                int width = *(int*)(messageData + 8);
                int height = *(int*)(messageData + 12);
                int chunkHeight = *(int*)(messageData + 16);
                int startY = *(int*)(messageData + 20);

                const char* sceneXml = messageData + 24;

                console.UpdateStatus(threadIndex + 1, "Thread ", threadIndex, ": Chunk requested.");
                console.AddHistory(threadIndex + 1, "Chunk requested.");

                //AcquireSRWLockExclusive(&workerThreadState->Lock);
                //while (workerThreadState->Status != WorkerStatus::ProcessingChunk)
                //    SleepConditionVariableSRW(&workerThreadState->ConditionVariable, &workerThreadState->Lock, INFINITE, 0);

                console.UpdateStatus(threadIndex + 1, "Thread ", threadIndex, ": Chunk received. Processing: 0%");
                console.AddHistory(threadIndex + 1, "Chunk received. Processing.");

                // Start the counter.
                LARGE_INTEGER startingTime, endingTime, frequency;

                QueryPerformanceFrequency(&frequency);
                QueryPerformanceCounter(&startingTime);

                // Render the scene.
                XmlSceneLoader xmlSceneLoader(sceneXml);

                MaterialContainer materialContainer;
                materialContainer.MaterialMap = xmlSceneLoader.ParseMaterialMap();
                materialContainer.SurfaceMaterialMap = new std::unordered_map<const Surface*, const MaterialBase*>();

                Scene* scene = xmlSceneLoader.CreateScene(&materialContainer);
                Camera* camera = xmlSceneLoader.CreateCamera();

                int antiAliasingLevel = scene->GetAntiAliasingLevel();
                int* sendBuffer = new int[width * chunkHeight + 4];

                Ray* rays = new Ray[antiAliasingLevel * antiAliasingLevel];
                for (int y = startY; y < startY + chunkHeight; ++y)
                {
                    for (int x = 0; x < width; ++x)
                    {
                        //if (x != 91 || y != 14)
                        //    continue;

                        camera->CalculateRays(x, y, antiAliasingLevel, rays);

                        Color3 color(0.0f);
                        for (int i = 0; i < antiAliasingLevel * antiAliasingLevel; ++i)
                            color += scene->CastRay(rays[i]);

                        color = color / (float)(antiAliasingLevel * antiAliasingLevel);

                        sendBuffer[(y - startY) * width + x + 4] = (int)(color.Blue * 255.0f) | ((int)(color.Green * 255.0f) << 8) | ((int)(color.Red * 255.0f) << 16);
                    }

                    int percentComplete = (double)(y - startY) / chunkHeight * 100.0;
                    console.UpdateStatus(threadIndex + 1, "Thread ", threadIndex, ": Chunk received. Processing: ", percentComplete, "%");
                }

                console.UpdateStatus(threadIndex + 1, "Thread ", threadIndex, ": Chunk received. Processing: 100%");

                // End the counter.
                QueryPerformanceCounter(&endingTime);

                double elapsed = endingTime.QuadPart - startingTime.QuadPart;
                elapsed *= 1000.0;
                elapsed /= frequency.QuadPart;

                console.UpdateStatus(threadIndex + 1, "Thread ", threadIndex, ": Chunk completed.");
                console.AddHistory(threadIndex + 1, "Chunk completed in ", elapsed, " milliseconds.");

                // Cleanup resources.
                delete scene;
                delete camera;

                sendBuffer[0] = 3;
                sendBuffer[1] = (width * chunkHeight + 4) * 4 - 8;
                sendBuffer[2] = sceneId;
                sendBuffer[3] = chunkId;

                auto result = network->Send((char*)sendBuffer, (width * chunkHeight + 4) * 4);

                console.UpdateStatus(threadIndex + 1, "Thread ", threadIndex, ": Sent completed chunk to server.");
                console.AddHistory(threadIndex + 1, "Sent completed chunk to server: ", result, " : ", WSAGetLastError());

                delete[] sendBuffer;
            }
        });

        tasks.push_back(task);
    }

    for (unsigned int i = 0; i < totalWorkingThreads; i++)
        tasks[i].wait();

    return 0;
}