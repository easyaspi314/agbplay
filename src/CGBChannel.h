#pragma once

#include <cstdint>
#include <cstddef>

#include "Types.h"

#define INVALID_OWNER 0xFF

namespace agbplay
{
    class CGBChannel
    {
        public: 
            CGBChannel();
            ~CGBChannel();
            virtual void Init(uint8_t owner, CGBDef def, Note note, ADSR env);
            virtual void Process(float *buffer, size_t nblocks, MixingArgs& args) = 0;
            uint8_t GetOwner();
            void SetVol(uint8_t vol, int8_t pan);
            uint8_t GetMidiKey();
            int8_t GetNoteLength();
            void Release();
            virtual void SetPitch(int16_t pitch) = 0;
            bool TickNote(); // returns true if note remains active
            EnvState GetState();
        protected:
            virtual void stepEnvelope();
            void updateVolFade();
            ChnVol getVol();
            enum class Pan { LEFT, CENTER, RIGHT };
            uint32_t pos;
            float interPos;
            float freq;
            ADSR env;
            Note note;
            CGBDef def;
            EnvState eState;
            EnvState nextState;
            Pan pan;
            uint8_t envInterStep;
            uint8_t envLevel;
            uint8_t envPeak;
            uint8_t envSustain;
            // these values are always 1 frame behind in order to provide a smooth transition
            Pan fromPan;
            uint8_t fromEnvLevel;
            uint8_t owner;
    };

    class SquareChannel : public CGBChannel
    {
        public:
            SquareChannel();
            ~SquareChannel();

            void Init(uint8_t owner, CGBDef def, Note note, ADSR env) override;
            void SetPitch(int16_t pitch) override;
            void Process(float *buffer, size_t nblocks, MixingArgs& args) override;

            const float *pat;
    };

    class WaveChannel : public CGBChannel
    {
        public:
            WaveChannel();
            ~WaveChannel();

            void Init(uint8_t owner, CGBDef def, Note note, ADSR env) override;
            void SetPitch(int16_t pitch) override;
            void Process(float *buffer, size_t nblocks, MixingArgs& args) override;
        private:
            float waveBuffer[32];
            static uint8_t volLut[16];
    };

    class NoiseChannel : public CGBChannel
    {
        public:
            NoiseChannel();
            ~NoiseChannel();

            void Init(uint8_t owner, CGBDef def, Note note, ADSR env) override;
            void SetPitch(int16_t pitch) override;
            void Process(float *buffer, size_t nblocks, MixingArgs& args) override;
    };
}
