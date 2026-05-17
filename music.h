#pragma once

#include "header.h"

#include <fstream>
#include <cstring>
#include <map>
#include <set>
#include <vector>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

#ifdef _WIN32
    #include <windows.h>
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
    #include <unistd.h>
#else
    #include <unistd.h>
#endif

#ifdef __APPLE__
    #include <OpenAL/al.h>
    #include <OpenAL/alc.h>
#else
    #include <AL/al.h>
    #include <AL/alc.h>
#endif









namespace Music
{
    static const string menuTrackPath = "gameTrack.wav";

    static const string gameplayTrackPath = "gameTrack.wav";

    static const string coinCollectPath = "coinSound.wav";

    static const string enemyHitPath = "faaah.wav";

    static const string winPath = "7crore.wav";

    // Volume levels (0.0 to 1.0) constexprs [Compile time constants]
    static constexpr float volume = 0.75f;
    static constexpr float sfxVolume = 0.90f;

    static ALCdevice* device = nullptr; 
    static ALCcontext* context = nullptr; 
    static ALuint musicSource = 0;
    static string currentTrackPath;

    static bool initialized = false;
    static bool warnedOpenALFailure = false;
    
    static std::set<string> warnedMissingPaths;
    static std::map<string, ALuint> bufferCache;
    static std::vector<ALuint> activeSfxSources;

    inline string executableDirectory()
    {
#ifdef _WIN32
        char buffer[MAX_PATH];
        DWORD length = GetModuleFileNameA(nullptr, buffer, MAX_PATH);
        if (length > 0 && length < MAX_PATH)
        {
            string executablePath(buffer, buffer + length);
            size_t separator = executablePath.find_last_of("\\/");
            if (separator != string::npos)
            {
                return executablePath.substr(0, separator);
            }
        }
        return ".";


#elif defined(__APPLE__)
        char buffer[1024];
        uint32_t size = sizeof(buffer);

        if (_NSGetExecutablePath(buffer, &size) == 0)
        {
            string executablePath(buffer);
            size_t separator = executablePath.find_last_of('/');
            if (separator != string::npos)
            {
                return executablePath.substr(0, separator);
            }
        }
        return ".";


#else
        char buffer[1024];
        ssize_t length = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
        if (length > 0)
        {
            buffer[length] = '\0';
            string executablePath(buffer);
            size_t separator = executablePath.find_last_of('/');
            if (separator != string::npos)
            {
                return executablePath.substr(0, separator);
            }
        }
        return ".";
#endif
    }




    

    // --------------------------------------------------------------------------------
    // If file is not found at given path, also check relative to executable directory
    // ---------------------------------------------------------------------------------
    inline string resolveTrackPath(const string& path)
    {
        if (path.empty())
        {
            return path;
        }

        if (ifstream(path, ios::binary).good())
        {
            return path;
        }

        const string executableRelativePath = executableDirectory() + "/" + path;
        if (ifstream(executableRelativePath, ios::binary).good())
        {
            return executableRelativePath;
        }

        return path;
    }
    // --------------------------------------------------------------------------------
    // If file is not found at given path, also check relative to executable directory
    // ---------------------------------------------------------------------------------









    // --------------------------------
    // check if track exists
    // --------------------------------
    inline bool trackExists(const string& path)
    {
        return !path.empty() && ifstream(resolveTrackPath(path), ios::binary).good();
    }
    // --------------------------------
    // check if track exists
    // --------------------------------










    // --------------------------------
    // OpenAL initialized
    // --------------------------------
    inline bool ensureInitialized()
    {
        if (initialized)
        {
            return true;
        }

        device = alcOpenDevice(nullptr);
        if (!device)
        {
            if (!warnedOpenALFailure)
            {
                cout << "OpenAL audio device could not be opened." << endl;
                warnedOpenALFailure = true;
            }
            return false;
        }

        context = alcCreateContext(device, nullptr);
        if (!context || !alcMakeContextCurrent(context))
        {
            if (!warnedOpenALFailure)
            {
                cout << "OpenAL audio context could not be created." << endl;
                warnedOpenALFailure = true;
            }

            if (context)
            {
                alcDestroyContext(context);
                context = nullptr;
            }

            alcCloseDevice(device);
            device = nullptr;
            return false;
        }

        alGenSources(1, &musicSource);
        alSourcef(musicSource, AL_GAIN, volume);
        alListener3f(AL_POSITION, 0.0f, 0.0f, 1.0f);
        alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
        const ALfloat orientation[] = {0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f};
        alListenerfv(AL_ORIENTATION, orientation);

        initialized = true;
        return true;
    }
    // --------------------------------
    // OpenAL initialized
    // --------------------------------









    // --------------------------------
    // Warning about missing files
    // --------------------------------
    inline void warnMissingOnce(const string& path)
    {
        if (warnedMissingPaths.insert(path).second)
        {
            cout << "Audio file not found: " << path << endl;
        }
    }
    // --------------------------------
    // Warning about missing files
    // --------------------------------










    // -----------------------------------------------
    // Waning about unsupported formats
    // -----------------------------------------------
    inline void warnUnsupportedFormatOnce(const string& path)
    {
        const string key = "unsupported:" + path;
        if (warnedMissingPaths.insert(key).second)
        {
            cout << "Unsupported audio format: " << path << endl;
            cout << "OpenAL loader expects PCM WAV files, not MP3 data." << endl;
        }
    }
    // -----------------------------------------------
    // Waning about unsupported formats
    // -----------------------------------------------







    // ----------------------------------------------------------------
    // read 2 bytes as unsigned 16-bit integer (little-endian)
    // ----------------------------------------------------------------
    template <typename T>
    inline bool readU16(ifstream& file, T& value)
    {
        unsigned char bytes[2];
        if (!file.read(reinterpret_cast<char*>(bytes), 2))
        {
            return false;
        }

        value = static_cast<ALuint>(bytes[0] | (bytes[1] << 8));
        return true;
    }
    // ----------------------------------------------------------------
    // read 2 bytes as unsigned 16-bit integer (little-endian)
    // ----------------------------------------------------------------







    // ----------------------------------------------------------------
    // Read 4 bytes as unsigned 32-bit integer (little-endian)
    // ----------------------------------------------------------------
    template <typename T>

    inline bool readU32(ifstream& file, T& value)
    {
        unsigned char bytes[4];
        if (!file.read(reinterpret_cast<char*>(bytes), 4))
        {
            return false;
        }

        value = static_cast<ALuint>(bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24));
        return true;
    }
    // ----------------------------------------------------------------
    // Read 4 bytes as unsigned 32-bit integer (little-endian)
    // ----------------------------------------------------------------








    // --------------------------------
    // Load WAV file
    // --------------------------------
    inline bool loadWavFile(const string& path, std::vector<char>& pcmData, ALenum& format, ALsizei& sampleRate)
    {
        ifstream file(path, ios::binary);
        if (!file)
        {
            return false;
        }

        char header[3];
        if (file.read(header, 3) && strncmp(header, "ID3", 3) == 0)
        {
            warnUnsupportedFormatOnce(path);
            return false;
        }

        file.clear();
        file.seekg(0, ios::beg);

        char riff[4];
        if (!file.read(riff, 4) || strncmp(riff, "RIFF", 4) != 0)
        {
            warnUnsupportedFormatOnce(path);
            return false;
        }

        ALuint chunkSize = 0;
        if (!readU32(file, chunkSize))
        {
            return false;
        }

        char wave[4];
        if (!file.read(wave, 4) || strncmp(wave, "WAVE", 4) != 0)
        {
            warnUnsupportedFormatOnce(path);
            return false;
        }

        ALuint audioFormat = 0;
        ALuint channels = 0;
        ALuint bitsPerSample = 0;
        bool fmtFound = false;
        bool dataFound = false;

        while (file && (!fmtFound || !dataFound))
        {
            char chunkId[4];
            if (!file.read(chunkId, 4))
            {
                break;
            }

            ALuint subChunkSize = 0;
            if (!readU32(file, subChunkSize))
            {
                return false;
            }

            if (strncmp(chunkId, "fmt ", 4) == 0)
            {
                if (!readU16(file, audioFormat) || !readU16(file, channels) || !readU32(file, sampleRate))
                {
                    return false;
                }

                file.ignore(6);
                if (!readU16(file, bitsPerSample))
                {
                    return false;
                }

                if (subChunkSize > 16)
                {
                    file.ignore(static_cast<std::streamsize>(subChunkSize - 16));
                }

                fmtFound = true;
            }
            else if (strncmp(chunkId, "data", 4) == 0)
            {
                pcmData.resize(subChunkSize);
                if (!file.read(pcmData.data(), static_cast<std::streamsize>(subChunkSize)))
                {
                    return false;
                }
                dataFound = true;
            }
            else
            {
                file.ignore(static_cast<std::streamsize>(subChunkSize));
            }

            if (subChunkSize % 2 != 0)
            {
                file.ignore(1);
            }
        }

        if (!fmtFound || !dataFound || audioFormat != 1)
        {
            return false;
        }

        if (channels == 1 && bitsPerSample == 8)
        {
            format = AL_FORMAT_MONO8;
        }
        else if (channels == 1 && bitsPerSample == 16)
        {
            format = AL_FORMAT_MONO16;
        }
        else if (channels == 2 && bitsPerSample == 8)
        {
            format = AL_FORMAT_STEREO8;
        }
        else if (channels == 2 && bitsPerSample == 16)
        {
            format = AL_FORMAT_STEREO16;
        }
        else
        {
            return false;
        }

        return true;
    }
    // --------------------------------
    // Load WAV file
    // --------------------------------









    // --------------------------------
    // Load audio file into buffer
    // --------------------------------
    inline ALuint loadBufferForPath(const string& path)
    {
        const string resolvedPath = resolveTrackPath(path);
        auto cached = bufferCache.find(resolvedPath);
        if (cached != bufferCache.end())
        {
            return cached->second;
        }

        std::vector<char> pcmData;
        ALenum format = 0;
        ALsizei sampleRate = 0;

        if (!loadWavFile(resolvedPath, pcmData, format, sampleRate))
        {
            warnMissingOnce(resolvedPath);
            return 0;
        }

        ALuint buffer = 0;
        alGenBuffers(1, &buffer);
        alBufferData(buffer, format, pcmData.data(), static_cast<ALsizei>(pcmData.size()), sampleRate);

        bufferCache[resolvedPath] = buffer;
        return buffer;
    }
    // --------------------------------
    // Load audio file into buffer
    // --------------------------------








    // --------------------------------
    // Cleanup finished sound effects
    // --------------------------------
    inline void cleanupFinishedSfx()
    {
        for (size_t i = 0; i < activeSfxSources.size();)
        {
            ALint state = AL_STOPPED;
            alGetSourcei(activeSfxSources[i], AL_SOURCE_STATE, &state);

            if (state == AL_STOPPED)
            {
                alDeleteSources(1, &activeSfxSources[i]);
                activeSfxSources.erase(activeSfxSources.begin() + static_cast<long>(i));
            }
            else
            {
                ++i;
            }
        }
    }
    // --------------------------------
    // Cleanup finished sound effects
    // --------------------------------








    // ------------------------------
    // Shutdown music
    // ------------------------------
    inline void shutdown()
    {
        if (!initialized)
        {
            return;
        }

        if (musicSource != 0)
        {
            alSourceStop(musicSource);
            alDeleteSources(1, &musicSource);
            musicSource = 0;
        }

        for (ALuint source : activeSfxSources)
        {
            alSourceStop(source);
            alDeleteSources(1, &source);
        }
        activeSfxSources.clear();

        for (const auto& entry : bufferCache)
        {
            if (entry.second != 0)
            {
                alDeleteBuffers(1, &entry.second);
            }
        }
        bufferCache.clear();

        alcMakeContextCurrent(nullptr);
        if (context)
        {
            alcDestroyContext(context);
            context = nullptr;
        }

        if (device)
        {
            alcCloseDevice(device);
            device = nullptr;
        }

        currentTrackPath.clear();
        initialized = false;
    }
    // ------------------------------
    // Shutdown music
    // ------------------------------







    // ------------------------------
    // Stop music [calling shutdown]
    // ------------------------------
    inline void stop()
    {
        shutdown();
    }
    // ------------------------------
    // Stop music [calling shutdown]
    // ------------------------------






    // --------------------------------
    // Start playing a track
    // --------------------------------
    inline void start(const string& path)
    {
        if (!ensureInitialized())
        {
            return;
        }

        const string resolvedPath = resolveTrackPath(path);
        const ALuint buffer = loadBufferForPath(resolvedPath);

        if (buffer == 0)
        {
            return;
        }

        if (currentTrackPath == resolvedPath)
        {
            ALint state = AL_STOPPED;
            alGetSourcei(musicSource, AL_SOURCE_STATE, &state);
            if (state == AL_PLAYING)
            {
                return;
            }
        }

        alSourceStop(musicSource);
        alSourcei(musicSource, AL_BUFFER, static_cast<ALint>(buffer));
        alSourcei(musicSource, AL_LOOPING, AL_TRUE);
        alSourcef(musicSource, AL_GAIN, volume);
        alSourcePlay(musicSource);

        currentTrackPath = resolvedPath;
    }
    // --------------------------------
    // Start playing a track
    // --------------------------------







    // --------------------------------
    // Sync Music with game state
    // --------------------------------
    inline void sync(bool inMenu)
    {
        if (!ensureInitialized())
        {
            return;
        }

        const string& desiredTrack = inMenu ? menuTrackPath : gameplayTrackPath;
        const string resolvedDesiredTrack = resolveTrackPath(desiredTrack);

        if (currentTrackPath != resolvedDesiredTrack)
        {
            start(desiredTrack);
        }
        else
        {
            ALint state = AL_STOPPED;
            alGetSourcei(musicSource, AL_SOURCE_STATE, &state);
            if (state != AL_PLAYING)
            {
                start(desiredTrack);
            }
        }

        cleanupFinishedSfx();
    }
    // --------------------------------
    // Sync Music with game state
    // --------------------------------






    // --------------------------------
    // One Time Play sound
    // --------------------------------
    inline void playDetached(const string& path)
    {
        if (!ensureInitialized())
        {
            return;
        }

        const string resolvedPath = resolveTrackPath(path);
        const ALuint buffer = loadBufferForPath(resolvedPath);
        if (buffer == 0)
        {
            return;
        }

        ALuint source = 0;
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, static_cast<ALint>(buffer));
        alSourcef(source, AL_GAIN, sfxVolume);
        alSourcePlay(source);
        activeSfxSources.push_back(source);
    }
    // --------------------------------
    // One Time Play sound
    // --------------------------------







    // ------------------------------
    // Coin collection sound
    // ------------------------------
    inline void playCoinCollect()
    {
        playDetached(coinCollectPath);
    }
    // ------------------------------
    // Coin collection sound
    // ------------------------------




    // ------------------------------
    // Enemy hit sound
    // ------------------------------
    inline void playEnemyHit()
    {
        playDetached(enemyHitPath);
    }
    // ------------------------------
    // Enemy hit sound
    // ------------------------------






    // ------------------------------
    // Win sound
    // ------------------------------
    inline void playWin()
    {
        playDetached(winPath);
    }
    // ------------------------------
    // Win sound
    // ------------------------------



}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif
