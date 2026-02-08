#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"

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

    // Configure Relay Pin
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW); // Start OFF (Option A)

    delay(1000);
    Serial.println("\nStarting Compressor Switch...");

    // Initialize the Node
    Node my_node;
    my_node = RMaker.initNode(NODE_NAME);

    // callback for standard Switch device
    my_switch.addCb(write_callback);

    // Add switch device to the node
    my_node.addDevice(my_switch);

    // Enable OTA
    RMaker.enableOTA(OTA_USING_PARAMS);

    // Enable Time Zone and Schedule
    // Commented out to avoid compilation errors with some library versions
    // RMaker.enableTZ();
    // RMaker.enableSchedule();

    // Show debug
    // Commented out to ensure compatibility with various ESP RainMaker library versions
    // Serial.printf("\nNode ID: %s\n", RMaker.getNodeID());

    // Register WiFi Event Handler
    WiFi.onEvent(sysProvEvent);

    // Start RainMaker
    RMaker.start();

    // If not provisioned, this will start provisioning.
    // Use the ESP RainMaker App to claim.
}

void loop() {
    // RainMaker runs in background task
    // Just keep the main loop alive
    delay(1000);
}
