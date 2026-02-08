#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"
#include <nvs_flash.h> // Include NVS Flash library

// Set the Relay Pin. GPIO 4 is a safe default for ESP32-C3.
#define RELAY_PIN 4

// Name of the node and device
#define NODE_NAME "Compressor Switch"
#define DEVICE_NAME "Compressor"

// Variable to store the relay pin for the callback
static int relay_pin = RELAY_PIN;

// The RainMaker Switch Device
static Switch my_switch(DEVICE_NAME, &relay_pin);

void sysProvEvent(arduino_event_t *sys_event) {
    switch (sys_event->event_id) {
        case ARDUINO_EVENT_PROV_START:
            Serial.println("\nProvisioning Started");
            break;
        case ARDUINO_EVENT_WIFI_STA_CONNECTED:
            Serial.println("\nConnected to Wi-Fi!");
            break;
        case ARDUINO_EVENT_PROV_CRED_RECV:
            Serial.println("\nProvisioning Credentials Received");
            break;
        case ARDUINO_EVENT_PROV_INIT:
            Serial.println("\nProvisioning Initialized");
            break;
        case ARDUINO_EVENT_PROV_CRED_SUCCESS:
            Serial.println("\nProvisioning Successful");
            break;
        case ARDUINO_EVENT_PROV_END:
            Serial.println("\nProvisioning End");
            break;
        case ARDUINO_EVENT_PROV_CRED_FAIL:
            Serial.println("\nProvisioning Failed");
            break;
        default:
            break;
    }
}

void write_callback(Device *device, Param *param, const param_val_t val, void *priv_data, write_ctx_t *ctx) {
    const char *device_name = device->getDeviceName();
    const char *param_name = param->getParamName();

    if (strcmp(device_name, DEVICE_NAME) == 0) {
        if (strcmp(param_name, "Power") == 0) {
            Serial.printf("Received value = %s for %s - %s\n", val.val.b ? "true" : "false", device_name, param_name);
            bool state = val.val.b;
            // Control the relay
            digitalWrite(RELAY_PIN, state ? HIGH : LOW);
            // Report the change back to the cloud
            param->updateAndReport(val);
        }
    }
}

void setup() {
    Serial.begin(115200);

    // On ESP32-C3 with Native USB (CDC), wait for Serial to connect
    // otherwise the first logs (like the QR code) might be missed.
    // Try to open Serial Monitor quickly after uploading!
    delay(3000);

    // Configure Relay Pin
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW); // Start OFF (Option A)

    Serial.println("\n==================================================");
    Serial.println("Starting Compressor Switch...");
    Serial.println("==================================================");

    // Initialize NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        Serial.println("NVS Partition was truncated and needs to be erased");
        Serial.println("Erasing NVS...");
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
    Serial.println("NVS Initialized successfully.");

    // Initialize the Node
    Serial.println("[DEBUG] Initializing RainMaker Node...");
    Node my_node;
    my_node = RMaker.initNode(NODE_NAME);

    // callback for standard Switch device
    my_switch.addCb(write_callback);

    Serial.println("[DEBUG] Adding Switch Device...");
    // Add switch device to the node
    my_node.addDevice(my_switch);

    Serial.println("[DEBUG] Enabling OTA...");
    // Enable OTA
    RMaker.enableOTA(OTA_USING_PARAMS);

    // Enable Time Zone and Schedule
    // Commented out to avoid compilation errors with some library versions
    // RMaker.enableTZ();
    // RMaker.enableSchedule();

    // Show debug
    // Commented out to ensure compatibility with various ESP RainMaker library versions
    // Serial.printf("\nNode ID: %s\n", RMaker.getNodeID());

    Serial.println("[DEBUG] Registering WiFi Events...");
    // Register WiFi Event Handler
    WiFi.onEvent(sysProvEvent);

    Serial.println("[DEBUG] Starting RainMaker...");
    // Start RainMaker
    RMaker.start();

    Serial.println("[DEBUG] RainMaker Start function returned. Running loop...");

    // If not provisioned, this will start provisioning.
    // Use the ESP RainMaker App to claim.
}

void loop() {
    // RainMaker runs in background task
    // Just keep the main loop alive
    delay(1000);
}
