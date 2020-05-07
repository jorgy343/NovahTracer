#include <SDKDDKVer.h>
#include <ppl.h>

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <tuple>

#include <winsock2.h>
#include <ws2tcpip.h>

#include "LuaState.h"
#include "AdvancedMathLuaExtensions.h"

using namespace Novah::Lua;

static unsigned int g_randomValue;
static uint32_t x, y, z, w;

inline void SeedRandom(int seed1, int seed2, int seed3, int seed4)
{
    g_randomValue = seed1;

    x = seed1;
    y = seed2;
    z = seed3;
    w = seed4;
}

inline int GetRandom()
{
    g_randomValue = 214013 * g_randomValue + 2531011;
    return (g_randomValue >> 16) & 0x7FFF;
}

inline uint32_t xorshift128();

inline float NormalizedRandom()
{
    //return (float)(GetRandom() % RAND_MAX) / (float)RAND_MAX;
    //return (float)(xorshift128() / (float)0xFFFFFFFF);

    union
    {
        float ranf;
        uint32_t rani;
    };
    
    g_randomValue *= 16807;
    rani = (g_randomValue & 0x7FFFFF) | 0x3F800000;
    ranf -= 1.0f;

    return ranf;

    //g_randomValue *= 16807;

    //return (float)(g_randomValue / (float)0xFFFFFFFF);
}

inline uint32_t xorshift128()
{
    uint32_t t = x;

    t ^= t << 11;
    t ^= t >> 8;
    x = y; y = z; z = w;
    w ^= w >> 19;
    w ^= t;

    return w;
}

int _tmain(int argc, _TCHAR* argv[])
{
    /*
    auto luaState = new LuaState();
    luaL_openlibs(luaState->GetInternalState());

    luaState->LoadStringAndExecute(R"strend(
        function shade(point, normal)
            local x = math.abs(math.floor((point.X + 0.001) / 5.0));
            local y = math.abs(math.floor((point.Y + 0.001) / 5.0));
            local z = math.abs(math.floor((point.Z + 0.001) / 5.0));
            
            local xmod = x % 2;
            local ymod = y % 2;
            local zmod = z % 2;
            
            if xmod == ymod and ymod == zmod then
                return {X = 0.4, Y = 0.8, Z = 0.4};
            else
                return {X = 1.0, Y = 1.0, Z = 1.0};
            end
        end
    )strend");

    Vector3 point(5.0, 3.0, 9.0);
    auto result = luaState->Call<Vector3>("shade", point);

    std::cout << result.X << " : " << result.Y << " : " << result.Z << std::endl;
    return 0;*/

    time_t currentTime;
    SeedRandom((int)time(&currentTime), (int)time(&currentTime) + 1, (int)time(&currentTime) + 2, (int)time(&currentTime) + 3);

    float finalResult = 0.0f;

    // Start the counter.
    LARGE_INTEGER startingTime, endingTime, frequency;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&startingTime);

    for (int i = 0; i < 10000000; i++)
    {
        finalResult += NormalizedRandom();
    }

    // End the counter.
    QueryPerformanceCounter(&endingTime);

    double elapsed = endingTime.QuadPart - startingTime.QuadPart;
    elapsed *= 1000.0;
    elapsed /= frequency.QuadPart;

    std::cout << "Elapsed milliseconds: " << elapsed << std::endl;

    for (int i = 0; i < 20; i++)
    {
        std::cout << NormalizedRandom() << std::endl;
    }

    return (int)finalResult;
}