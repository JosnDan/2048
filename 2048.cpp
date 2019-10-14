#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<ctype.h>
#include<graphics.h>
#include<string.h>
#include<dos.h>
#include<fstream.h>
#include<stdlib.h>
#define BGI "c:\\turboc3\\bgi"


void text3D(int x, int y, int depth, int bgcolor, int fgcolor,int font,int size, char *caption)
{
  int i;
  setcolor(bgcolor);
  settextstyle(font,HORIZ_DIR,size);
  for(i=0; i<depth; i++)
    outtextxy(x+i,y+i,caption);
  setcolor(fgcolor);
  outtextxy(x+i,y+i,caption);

}


class Element;
class Board;

class Element
{
  int value,row,col,colour,size;
public:
  static int trow,tcol,boardLeft,boardTop;
  static Board *base;
  Element(int value,int row,int col,int size)
  {
    this->size=size;
    this->value=value;
    this->row=row;
    this->col=col;
    colour=1;
  }
  int getValue()
  {
    return value;
  }
  void Double()
  {
    value*=2;
    colour++;
  }
  int fallDown()
  {
    int flag=0;
    for(int i=row+1;i<trow;i++)
    {
      if(base->isFree(i,col))
      {
        flag=1;
        base->move(row,col,i,col);
        row=i;
      }
      else if(value==base->getValue(i,col))
      {
        base->merge(row,col,i,col);
        return -1;
      }
      else if(flag)
        break;
    }
    return row;
  }
  int fallUp()
  {
    int flag=0;
    for(int i=row-1;i>=0;i--)
    {
      if(base->isFree(i,col))
      {
        flag=1;
        base->move(row,col,i,col);
        row=i;
      }
      else if(value==base->getValue(i,col))
      {
        base->merge(row,col,i,col);
        return -1;
      }
      else if(flag)
        break;
    }
    return row;
  }
  int fallRight()
  {
    int flag=0;
    for(int i=col+1;i<tcol;i++)
    {
      if(base->isFree(row,i))
      {
        flag=1;
        base->move(row,col,row,i);
        col=i;
      }
      else if(value==base->getValue(row,i))
      {
        base->merge(row,col,row,i);
        return -1;
      }
      else if(flag)
        break;
    }
    return col;
  }
  int fallLeft()
  {
    int flag=0;
    for(int i=col-1;i>=0;i--)
    {
      if(base->isFree(row,i))
      {
        flag=1;
        base->move(row,col,row,i);
        col=i;
      }
      else if(value==base->getValue(row,i))
      {
        base->merge(row,col,row,i);
        return -1;
      }
      else if(flag)
        break;
    }
    return col;
  }
  void disp()
  {
    char st[10];
    if(colour>getmaxcolor())
      colour=1;
    setfillstyle(SOLID_FILL,colour);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,1);
    int left=boardLeft+col*size,top=boardTop+row*size,bottom,right;
    right=left+size;
    bottom=top+size;
    bar(left,top,right,bottom);
    sprintf(st,"%d",value);
    outtextxy((left+right)/2,(top+bottom)/2,st);
  }
};

class Board
{
  int trow,tcol;
  int size,colour;
  int right,left,top,bottom;
  Element ***base;
public:
  Board(int trow=4,int tcol=4,int size=50)
  {
    this->size=size;
    this->trow=trow;
    this->tcol=tcol;
    int l=size*trow,b=size*tcol;
    Element::boardLeft=left=(getmaxx()/2)-(l/2);
    Element::boardTop=top=(getmaxy()/2)-(b/2);
    right=left+l;
    bottom=top+b;
    base =new Element**[trow];
    for(int i=0;i<trow;i++)
    {
      base[i]=new Element*[tcol];
      for(int j=0;j<tcol;j++)
      {
        base[i][j]=NULL;
      }
    }
  }
  void drawBoard()
  {
    setfillstyle(SOLID_FILL,0);
    setcolor(LIGHTCYAN);
    bar(left,top,right,bottom);
  }
  void showBoard()
  {
    drawBoard();
    for(int i=0;i<trow;i++)
    {
      for (int j = 0; j < tcol; j++)
      {
        if(!isFree(i,j))
         base[i][j]->disp();
     }
   }
 }
 ~Board()
 {
  for(int i=0;i<trow;i++)
  {
    for(int j=0;j<tcol;j++)
    {
      delete base[i][j];
    }
    delete base[i];
  }
  delete base;
}
int getValue(int row,int col)
{
  return base[row][col]->getValue();
}
void merge(int r1,int c1,int r2,int c2)
{
  base[r2][c2]->Double();
  delete base[r1][c1];
  base[r1][c1]=NULL;
}
int isFree(int row,int col)
{
  if (base[row][col]==NULL)
  {
    return 1;
  }
  return 0;
}
int createElement()
{
  int val=random(2)+1,flag=0;
  val*=2;
  for(int i=0;i<trow;i++)
  {
    for (int j = 0; j < tcol; ++j)
    {
      if(isFree(i,j))
      {
        flag=1;
        base[i][j]=new Element(val,i,j,size);
        break;
      }
    }
    if(flag==1)
     break;
 }
 return flag;
}
void swipeRight()
{
  int dum=-1;
  for (int i = 0; i < trow; ++i)
  {
    for(int j=tcol-1;j>=0;j--)
    {
      if(!isFree(i,j))
      {
        dum=base[i][j]->fallRight();

      }
    }
  }
}
void swipeLeft()
{
  for (int i = 0
    ; i < trow; ++i)
  {
    for(int j=0;j<tcol;j++)
    {
      if(!isFree(i,j))
      {
        int c=base[i][j]->fallLeft();
      }
    }
  }
}
void swipeDown()
{
  for (int i = 0; i < tcol; ++i)
  {
    for(int j=trow-1;j>=0;j--)
    {
      if(!isFree(j,i))
      {
        int r=base[j][i]->fallDown();
      }
    }
  }
}
void swipeUp()
{
  for (int i = 0; i < tcol; ++i)
  {
    for(int j=0;j<trow;j++)
    {
      if(!isFree(j,i))
      {
        int r=base[j][i]->fallUp();
      }
    }
  }
}

void move(int i,int j,int r,int c)
{
  base[r][c]=base[i][j];
  if(i!=r || j!=c)
   base[i][j]=NULL;
}
void play()
{
  int live=1;
  char key='s';
  text3D(233,220,6,GREEN,LIGHTGREEN,DEFAULT_FONT,4,"2046");

  char a[2];
  for(int i=200; i<=440; i+=1)
  {
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(200,280,i,290);
    setcolor(WHITE);
    settextstyle(0,HORIZ_DIR,1.5);
    outtextxy(200,270,"Loading....");
    delay(15);
  }
  setcolor(BLACK);
  settextstyle(0,HORIZ_DIR,1.5);
  outtextxy(200,270,"Loading....");
  setcolor(WHITE);
  outtextxy(200,270,"GameLoaded");
  delay(20);
  do
  {
    live=createElement();
    showBoard();
    if(!live)
      break;
    key=getch();
    switch(key)
    {
      case 'a': swipeLeft();
      break;
      case 'd': swipeRight();
      break;
      case 's': swipeDown();
      break;
      case 'w':  swipeUp();
      break;
    }
    cleardevice();
  }while(key!='e');
  if(key=='e')
    outtext("Thank You");
  else
    outtext("Game over");
  getch();
}
};


