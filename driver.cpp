#include"2048.cpp"

Board *Element::base;
int Element::trow,Element::tcol,Element::boardLeft,Element::boardTop;

void main()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"c:\\turboc3\\bgi");
    cleardevice();
    int r=4,c=4;
    Element::trow=r;
    Element::tcol=c;
    Board Game(r,c);
    Element::base=&Game;
    Game.play();
    closegraph();
}
