#include <windows.h>

BOOL WINAPI ConsoleCtrlHandler(DWORD ctrlType) {
    switch (ctrlType) {
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        // std::cout << "���O�I�t�܂��̓V���b�g�_�E���C�x���g���������܂����B �v���O�������I�����܂��B" << std::endl;
        ExitProcess(0);  // �����Ƀv���O�������I��
        return TRUE;  // �C�x���g�������������Ƃ��V�X�e���ɒʒm
    default:
        return FALSE; // ���̃C�x���g�͏������Ȃ�
    }
}

