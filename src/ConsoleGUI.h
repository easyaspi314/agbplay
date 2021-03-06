#pragma once

#define CONSOLE_BORDER_WIDTH 2

#include <vector>
#include <string>

#include "CursesWin.h"

namespace agbplay {
    class ConsoleGUI : public CursesWin {
        public:
            ConsoleGUI(uint32_t height, uint32_t width, 
                    uint32_t yPos, uint32_t xPos);
            ~ConsoleGUI();
            void Resize(uint32_t height, uint32_t width,
                    uint32_t yPos, uint32_t xPos) override;
            void WriteLn(const std::string& str);
        private:
            void update() override;
            void writeToBuffer(const std::string& str);
            static void remoteWrite(const std::string& str, void *obj);

            uint32_t textWidth, textHeight;
            std::vector<std::string> textBuffer;
    };
}
