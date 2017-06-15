#include<KrWindow>


class KrControl
{
    private:
        RECT m_rect;

    public:
        RECT*   GetRect();//
		void    SetRect(RECT* pRect); //
        int     GetX();//
 		int     GetY();//
 		int     GetWidth();//
 		int     GetHeight();//
 		void    SetX(int x);//
 		void    SetY(int y);//
 		void    SetWidth(int width);//
 		void    SetHeight(int height);//
        void    Update();
}