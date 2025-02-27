﻿#include "mongoose.h"   // To build, run: cc main.c mongoose.c
#include <iostream>

#include <string>

// HTTP server event handler function
void ev_handler(struct mg_connection* c, int ev, void* ev_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message* hm = (struct mg_http_message*)ev_data;
//        struct mg_http_serve_opts opts = { .root_dir = "./web_root/" };
        struct mg_http_serve_opts opts = { .root_dir = "./" };
        mg_http_serve_dir(c, hm, &opts);
    }
}

extern void BindWindow(HWND hWnd);
extern bool IsBindWindowClosed();
extern int getAvailablePort();
extern BOOL WINAPI ConsoleCtrlHandler(DWORD ctrlType);

int main(int argc, char* argv[]) {
    using namespace std;

    // コンソール制御ハンドラを設定
    SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);

    if (argc >= 2) {
        // 一番目の引数があれば、そのウィンドウがなくなったら、このプロセスも終了する
        HWND hWnd = (HWND)(std::stoul(argv[1], nullptr));
        BindWindow(hWnd);
    }

    // 空いているポートを探す。やや時間はかかるが確実性が段違い。
    int port = getAvailablePort();
    if (port <= 0) {
        port = 0;
        cout << 0 << endl; // flush兼ねる
        return 1;
    }

    // URLの構築
    string url = "http://localhost:" + to_string(port);

    struct mg_mgr mgr;  // Declare event manager
    mg_mgr_init(&mgr);  // Initialise event manager

    // リスナー開始
    mg_connection *ret = mg_http_listen(&mgr, url.c_str(), ev_handler, NULL);  // Setup listener
    if (ret == NULL) {
        cout << 0 << endl; // flush兼ねる
        return 1;
    }

    cout << port << endl; // flush兼ねる

    // イベントループ
    while (true) {

		// 結びつけていたウィンドウが閉じてしまっているなら、このプロセスも終了する
		if (IsBindWindowClosed()) {
			break;
		}

        mg_mgr_poll(&mgr, 1000);
    }
    return 0;
}