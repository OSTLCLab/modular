#ifndef EINKCOMMUNICATION_H
#define EINKCOMMUNICATION_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_EPD.h>
#include <framework/Communication.h>
#include <string>



namespace modular::devices::arduino {

class EInkCommunication  : public Communication<std::string> {
public:
        EInkCommunication(int width, int height, int16_t DC, int16_t RST, int16_t CS, int16_t SRCS, int16_t BUSY) : 
        display{width, height, DC, RST, CS, SRCS, BUSY}
        //m_width{width}, m_height{height}, m_DC{DC}, m_RST{RST}, m_CS{CS}, m_SRCS{SRCS}
        {
            //Adafruit_SSD1675 t = new Adafruit_SSD1675()
        };

        void logo() {
            display.begin();
            display.setRotation(0);
            display.clearBuffer();
            display.setTextWrap(true);
            display.setCursor(10, 20);
            display.setTextSize(2);
            display.setTextColor(EPD_BLACK);
            display.print("Welcome to modular");
            display.setCursor(10, 50);
            display.setTextSize(3);
            display.print("boilerplate");
            display.display();
        }

        void listen() {
            // No implementation possible for display
        };
        void send(std::string value) {
            debugLn("Update Display...");
            display.begin();
            display.clearBuffer();
            display.setCursor(10, 20);
            display.setTextSize(1);
            display.setTextColor(EPD_BLACK);
            int line = 0;
            int textwidth = 30;
            for (unsigned i = 0; i < value.length(); i += textwidth) {
                display.setCursor(10, 20+line);
                display.print(value.substr(i, textwidth).c_str());
                line += 10;
            }
            
            display.display();
        };
private: 
    /*int m_width; 
    int m_height; 
    int16_t m_DC;
    int16_t m_RST;
    int16_t m_CS; 
    int16_t m_SRCS;*/
    Adafruit_SSD1675 display;
};

}

#endif