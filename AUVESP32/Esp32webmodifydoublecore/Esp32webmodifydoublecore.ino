#include <WiFi.h>
#include <WebSocketsServer.h>
#include <TaskScheduler.h>
#include "Pagelndex.h"

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

WebSocketsServer webSocket = WebSocketsServer(80);
Scheduler scheduler;
Task taskCore1(2000, TASK_FOREVER, &core1Task);

void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    if (type == WStype_TEXT) {
        // 收到 WebSocket 文本消息
        String message = String((char*)payload);
        // 在这里解析和处理 WebSocket 指令
        if (message == "control_command_1") {
            // 执行控制命令 1
        } else if (message == "control_command_2") {
            // 执行控制命令 2
        }
    }
}

void core0Task(void *pvParameters) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }
    webSocket.begin();
    webSocket.onEvent(onWebSocketEvent);

    while (1) {
        webSocket.loop();
    }
}

void core1Task(void *pvParameters) {
    taskCore1.enable();
    while (1) {
        // 在此编写核心 1 上的慢速控制逻辑
        taskCore1.execute();
    }
}

void setup() {
    Serial.begin(115200);
    scheduler.init();
    
    xTaskCreatePinnedToCore(core0Task, "Core 0 Task", 8192, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(core1Task, "Core 1 Task", 8192, NULL, 1, NULL, 1);
}

void loop() {
    // 空主循环
}
