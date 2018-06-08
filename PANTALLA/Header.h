#pragma once

struct Pixel_RGBA
{
	int red;
	int green;
	int blue;
	int alpha;
};

class Canvas
{
public:
	Canvas(int, int);
	~Canvas();
	int Largo, Ancho;
	int BPP = 4;
	int pitch = Largo*BPP;
	Pixel_RGBA* pantalla = new Pixel_RGBA[Largo*Ancho];
private:
	void Put_pixel(int, int, Pixel_RGBA);
	void Line(int, int, int, int, Pixel_RGBA);
	void circle(int, int, int, Pixel_RGBA);
	void elipse(int, int, int, Pixel_RGBA);
	void rectangle(int, int, int, int, Pixel_RGBA);
	void BitBlit(Canvas*, int x, int y, int yinix, int iniy, int endx, int endy);
	void BitBlit(Canvas*, int x, int y);
	Pixel_RGBA getpixel(int, int);
};

Canvas::Canvas(int W, int H)
{
	Largo = W;
	Ancho = H;
}

void Canvas::Put_pixel(int x, int y, Pixel_RGBA color)
{
	pantalla[(x * 4) + (y*Largo)] = color;
}

Pixel_RGBA Canvas::getpixel(int X, int Y)
{
	return pantalla[(X)+(Y*Largo)];
}


void Canvas::Line(int x1, int y1, int x2, int y2, Pixel_RGBA color)
{
	int pendiente;
	int dx, dy, incE, incNE, d, x, y;
	if (x1 > x2)
	{
		Line(x2, y2, x1, y1, color);
		return;
	}
	dx = x2 - x1;
	dy = y2 - y1;

	if (dy < 0)
	{
		pendiente = -1;
		dy = -dy;
	}
	else
	{
		pendiente = 1;
	}

	incE = 2 * dy;
	incNE = 2 * dy - 2 * dx;
	d = 2 * dy - dx;
	y = y1;
	for (x = x1; x <= x2; x++)
	{
		Put_pixel(x, y, color);
		if (d <= 0)
		{
			d += incE;
		}
		else
		{
			d += incNE;
			y += pendiente;
		}
	}
}

void Canvas::rectangle(int x, int y, int largo, int ancho, Pixel_RGBA color)
{
	Line(x, y, x + largo, y, color);
	Line(x + largo, y, x + largo, y + ancho, color);
	Line(x + largo, y + ancho, x, y + ancho, color);
	Line(x, y + ancho, x, y, color);
}


void Canvas::circle(int X, int Y, int radio, Pixel_RGBA color)
{
	int f = 1 - radio;
	int ddF_x = 1;
	int ddF_y = -2 * radio;
	int x = 0;
	int y = radio;
	Put_pixel(X, Y + radio, color);
	Put_pixel(X, Y - radio, color);
	Put_pixel(X + radio, Y, color);
	Put_pixel(X - radio, Y, color);
	while (x < y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		Put_pixel(X + x, Y + y, color);
		Put_pixel(X - x, Y + y, color);
		Put_pixel(X + x, Y - y, color);
		Put_pixel(X - x, Y - y, color);
		Put_pixel(X + y, Y + x, color);
		Put_pixel(X - y, Y + x, color);
		Put_pixel(X + y, Y - x, color);
		Put_pixel(X - y, Y - x, color);
	}
}

void Canvas::elipse(int x0, int y0, int radio, Pixel_RGBA color)
{
	int
		x = -radio, y = 0, err = 2 - 2 * radio;
	do
	{
		Put_pixel(x0 - x, y0 + y, color);
		Put_pixel(x0 - y, y0 - x, color);
		Put_pixel(x0 + x, y0 - y, color);
		Put_pixel(x0 + y, y0 + x, color);
		radio = err;
		if (radio > x)
		{
			err += x++ * 2 + 1;
		}
		if (radio <= y)
		{
			err += y++ * 2 + 1;
		}
	} while (x < 0);
}

void Canvas::BitBlit(Canvas* imagen, int x, int y)
{
	for (size_t j = 0; j <= imagen->Ancho; j++)
	{
		for (size_t i = 0; i <= imagen->Largo; i++)
		{
			if (x + i > 0 || this->Largo > x + i)
			{
				if (y + j > 0 || this->Ancho > y + i)
				{
					this->pantalla[(x + i) + ((y + j)*Largo)] = imagen->pantalla[(x)+(y*Largo)];
				}
			}
		}
	}

}

void Canvas::BitBlit(Canvas* imagen, int x, int y, int inix, int iniy, int endx, int endy)
{
	int tam_x = endx - inix, tam_y = endy - iniy;
	for (size_t j = 0; j <= tam_y; j++)
	{
		for (size_t i = 0; i <= tam_x; i++)
		{
			if (x + i > 0 || this->Largo > x + i)
			{
				if (y + j > 0 || this->Ancho > y + i)
				{
					this->pantalla[(x + i) + ((y + j)*Largo)] = imagen->pantalla[(x + inix) + ((y + iniy)*Largo)];
				}
			}
		}
	}



}


Canvas::~Canvas()
{
}