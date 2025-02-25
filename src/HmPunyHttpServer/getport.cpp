#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int getAvailablePort() {
    // Winsock�̏�����
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return -1; // ���������s
    }

    // �\�P�b�g�쐬
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        WSACleanup();
        return -1; // �\�P�b�g�쐬���s
    }

    // �|�[�g�������I�ɑI�����邽�߂̐ݒ�
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = 0; // �|�[�g�ԍ���0�ɐݒ肷��ƁA�V�X�e�����󂢂Ă���|�[�g��I�����܂�

    // �o�C���h�����s
    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        closesocket(sock);
        WSACleanup();
        return -1; // �o�C���h���s
    }

    // �g�p���̃|�[�g���擾
    int addrLen = sizeof(addr);
    if (getsockname(sock, (struct sockaddr*)&addr, &addrLen) == SOCKET_ERROR) {
        closesocket(sock);
        WSACleanup();
        return -1; // �|�[�g�擾���s
    }

    // �N���[���A�b�v
    int port = ntohs(addr.sin_port);
    closesocket(sock);
    WSACleanup();

    return port; // �󂢂Ă���|�[�g�ԍ���Ԃ�
}
