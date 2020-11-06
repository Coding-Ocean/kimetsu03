#include"libOne.h"
void gmain() {
    window(1920, 1080, full);
    ShowCursor(FALSE);
    //���_�i����j�ɒ��S������悤�ɐ��O�p�`������
    angleMode(DEGREES);
    SHAPE_VERTEX v[] = {
        sin(0),-cos(0),
        sin(120),-cos(120),
        sin(240),-cos(240)
    };
    int shapeIdx = createShape(v, 3);
    //�O�p�`�̕\���A�ʒu�A�p�x�A�T�C�Y
    float x, y, a, s;
    a = 0;
    s = 20;
    //���Ă悱�ɕ��ׂ邽�߂̕ϐ�
    int rows = 18;
    float dy = height / (rows - 1);
    int cols = 32;
    float dx = width / (cols - 1);
    //�O�p�`�������ʒu���W�̎��Ɉړ������邽�߂̕ϐ�
    float deg = 0;
    float rotSpeed = 1;
    float cx = width / 2;
    float cy = height / 2;
    //�w�i�O���f�[�V�����`�悷��or���Ȃ�
    int drawLineFlag = 1;
    while (notQuit) {
        //�w�i�O���f�[�V����---------------------------------------
        if (isTrigger(KEY_SPACE)) {
            drawLineFlag = 1 - drawLineFlag;
        }
        if (drawLineFlag) {
            colorMode(HSV);
            for (int i = 0; i < 1080; i++) {
                float hue = map((float)i, 0, 1080, 60, 30);
                stroke(hue, 255, 255, 64);
                line(0, (float)i, width, (float)i);
            }
        }
        //�g���C�A���O���X----------------------------------------
        if (isPress(KEY_D))s += 1;
        if (isPress(KEY_A))s += -1;
        if (isPress(KEY_W))rotSpeed += 0.1f;
        if (isPress(KEY_S))rotSpeed += -0.1f;
        deg += rotSpeed;
        float mx = cx + cos(deg) * (cx - 200);
        float my = cy - sin(deg * 2) * (cy - 200);
        //�s��ɕ��ׂĕ`��̂Q�d���[�v
        colorMode(RGB);
        fill(255);
        stroke(128);
        for (int j = 0; j < rows; j++) {
            y = dy * j;
            //�T�C�Y���V�O�𒴂�����֊s�̐F��ς���
            if (s > 70) {
                colorMode(HSV);
                float hue = map(y, 0, 1080, 60, 420);
                stroke(hue, 255, 255);
                colorMode(RGB);
                fill(255, 255, 255, 200);
            }
            for (int i = 0; i < cols; i++) {
                float diff = (j % 2) * (dx / 2);
                x = diff + dx * i;
                //mx,my�̕����Ɍ�����
                a = atan2(-(x - mx), y - my);
                shape(shapeIdx, x, y, a, s);
            }
        }
    }
    ShowCursor(TRUE);
}
