
extern void Run();
extern bool OpenWindow(int _Width, int _Height, const char* _pTitle);
extern void CloseWindow();
extern void DrawPixel(int _X, int _Y);

/* signum function */
int sgn(int x)
{
    return (x > 0) ? 1 : (x < 0) ? -1 : 0;
}

void gbham(int xstart, int ystart, int xend, int yend)
/*--------------------------------------------------------------
 * Bresenham-Algorithmus: Linien auf Rastergeräten zeichnen
 *
 * Eingabeparameter:
 *    int xstart, ystart        = Koordinaten des Startpunkts
 *    int xend, yend            = Koordinaten des Endpunkts
 *
 * Ausgabe:
 *    void SetPixel(int x, int y) setze ein Pixel in der Grafik
 *         (wird in dieser oder aehnlicher Form vorausgesetzt)
 *---------------------------------------------------------------
 */
{
    int x, y, t, dx, dy, incx, incy, pdx, pdy, ddx, ddy, deltaslowdirection, deltafastdirection, err;

    /* Entfernung in beiden Dimensionen berechnen */
    dx = xend - xstart;
    dy = yend - ystart;

    /* Vorzeichen des Inkrements bestimmen */
    incx = sgn(dx);
    incy = sgn(dy);
    if(dx < 0) dx = -dx;
    if(dy < 0) dy = -dy;

    /* feststellen, welche Entfernung größer ist */
    if(dx > dy)
    {
        /* x ist schnelle Richtung */
        pdx = incx; pdy = 0;    /* pd. ist Parallelschritt */
        ddx = incx; ddy = incy; /* dd. ist Diagonalschritt */
        deltaslowdirection = dy;   deltafastdirection = dx;   /* Delta in langsamer Richtung, Delta in schneller Richtung */
    }
    else
    {
        /* y ist schnelle Richtung */
        pdx = 0;    pdy = incy; /* pd. ist Parallelschritt */
        ddx = incx; ddy = incy; /* dd. ist Diagonalschritt */
        deltaslowdirection = dx;   deltafastdirection = dy;   /* Delta in langsamer Richtung, Delta in schneller Richtung */
    }

    /* Initialisierungen vor Schleifenbeginn */
    x = xstart;
    y = ystart;
    err = deltafastdirection / 2;
    DrawPixel(x, y);

    /* Pixel berechnen */
    for(t = 0; t < deltafastdirection; ++t) /* t zaehlt die Pixel, deltafastdirection ist Anzahl der Schritte */
    {
        /* Aktualisierung Fehlerterm */
        err -= deltaslowdirection;
        if(err < 0)
        {
            /* Fehlerterm wieder positiv (>=0) machen */
            err += deltafastdirection;
            /* Schritt in langsame Richtung, Diagonalschritt */
            x += ddx;
            y += ddy;
        }
        else
        {
            /* Schritt in schnelle Richtung, Parallelschritt */
            x += pdx;
            y += pdy;
        }
        DrawPixel(x, y);
    }
} /* gbham() */
// -----------------------------------------------------------------------------
// Draws a line from (X1,Y1) to (X2,Y2).
// -----------------------------------------------------------------------------
void DrawLine(int _X1, int _Y1, int _X2, int _Y2)
{
    // Draws a horizontal line at the moment. 
    // Change this to draw an arbitrary line.
    /*
    for (int X = _X1; X < _X2; ++ X)
    {
        DrawPixel(X, _Y1);
    }
    */
}

// -----------------------------------------------------------------------------
// Callback which indicates that the window is drawn.
// -----------------------------------------------------------------------------
void OnDraw()
{
    // Add another DrawLine command here if you want to draw multiple lines.
    //DrawLine(20, 100, 620, 100);
    gbham(20, 400, 620, 200);
}

void main()
{
    OpenWindow(640, 480, "GDV Lesson 2");

    Run();

    CloseWindow();
}