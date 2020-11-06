#include"libOne.h"
void gmain() {
    window(1920, 1080, full);
    ShowCursor(FALSE);
    //原点（左上）に中心がくるように正三角形をつくる
    angleMode(DEGREES);
    SHAPE_VERTEX v[] = {
        sin(0),-cos(0),
        sin(120),-cos(120),
        sin(240),-cos(240)
    };
    int shapeIdx = createShape(v, 3);
    //三角形の表示、位置、角度、サイズ
    float x, y, a, s;
    a = 0;
    s = 20;
    //たてよこに並べるための変数
    int rows = 18;
    float dy = height / (rows - 1);
    int cols = 32;
    float dx = width / (cols - 1);
    //三角形が向く位置を８の字に移動させるための変数
    float deg = 0;
    float rotSpeed = 1;
    float cx = width / 2;
    float cy = height / 2;
    //背景グラデーション描画するorしない
    int drawLineFlag = 1;
    while (notQuit) {
        //背景グラデーション---------------------------------------
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
        //トライアングルス----------------------------------------
        if (isPress(KEY_D))s += 1;
        if (isPress(KEY_A))s += -1;
        if (isPress(KEY_W))rotSpeed += 0.1f;
        if (isPress(KEY_S))rotSpeed += -0.1f;
        deg += rotSpeed;
        float mx = cx + cos(deg) * (cx - 200);
        float my = cy - sin(deg * 2) * (cy - 200);
        //行列に並べて描画の２重ループ
        colorMode(RGB);
        fill(255);
        stroke(128);
        for (int j = 0; j < rows; j++) {
            y = dy * j;
            //サイズが７０を超えたら輪郭の色を変える
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
                //mx,myの方向に向ける
                a = atan2(-(x - mx), y - my);
                shape(shapeIdx, x, y, a, s);
            }
        }
    }
    ShowCursor(TRUE);
}
