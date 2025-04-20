#include "BleMidiSelector.h"
#include <BLEMidi.h>
#include "display.h"
#include <M5Dial.h>

extern Display display;

static int scanMidiDevices() {
    display.clear();
    display.drawText(display.width() / 2, display.height() / 2, "検索中", WHITE, middle_center, true);

    int count = 0;

    while (count == 0) {
        count = BLEMidiClient.scan();

        if (count == 0) {
            delay(200);
        }
    }

    return count;
}

static void showDeviceNames(int selected_index, std::vector<String> &device_names) {
    const int SELECTED_OFFSET_X = 10;
    const int NOT_SELECTED_OFFSET_X = 25;
    if (selected_index < 0 || device_names.size() <= selected_index) {
        return;
    }
    display.clear();
    
    if (selected_index > 0) {
        display.drawText(NOT_SELECTED_OFFSET_X, display.height() / 2 - display.TEXT_HEIGHT, device_names[selected_index - 1], TFT_WHITE, middle_left);
    }

    display.fillRect(0, display.height() / 2 - display.TEXT_HEIGHT / 2, display.width(), display.TEXT_HEIGHT, TFT_WHITE);
    display.drawText(SELECTED_OFFSET_X, display.height() / 2, device_names[selected_index], TFT_BLACK, middle_left);

    if (selected_index < device_names.size() - 1) {
        display.drawText(NOT_SELECTED_OFFSET_X, display.height() / 2 + display.TEXT_HEIGHT, device_names[selected_index + 1], TFT_WHITE, middle_left);
    }

    display.update();
}

static void connectMidiDevice(int index) {
    display.clear();
    display.drawText(display.width() / 2, display.height() / 2, "接続中", WHITE, middle_center, true);

    BLEMidiClient.connect(index);
    int retry_count = 0;
    while (!BLEMidiClient.isConnected()) {
        delay(100);
        retry_count++;
        if (retry_count > 10) {
            return;
        }
    }
}

static void selectMidiDevice(int count) {
    int selected_index = 0;

    std::vector<String> device_names(count + 1);
    for (int i = 0; i < count; i++) {
        NimBLEAdvertisedDevice* device = BLEMidiClient.getScannedDevice(i);
        device_names[i] = String(device->getName().c_str());
    }
    device_names[count] = "再検索";

    showDeviceNames(selected_index, device_names);

    long old_enc = M5Dial.Encoder.readAndReset();
    while (!BLEMidiClient.isConnected()) {
        M5Dial.update();

        long new_enc = M5Dial.Encoder.read();

        if (new_enc < old_enc - 3 && selected_index > 0) {
            selected_index--;
            showDeviceNames(selected_index, device_names);
            old_enc = new_enc;
        } else if (new_enc > old_enc + 3 && selected_index < device_names.size() - 1) {
            selected_index++;
            showDeviceNames(selected_index, device_names);
            old_enc = new_enc;
        } else if (M5Dial.BtnA.wasPressed()) {
            if (selected_index < count) {
                connectMidiDevice(selected_index);
            }

            return;
        }
    }
}

bool connectBleMidiDevice() {
    int count = scanMidiDevices();
    // return false;
    selectMidiDevice(count);

    return BLEMidiClient.isConnected();
}