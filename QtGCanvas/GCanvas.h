#ifndef GCANVAS_H
#define GCANVAS_H

class GCanvas
{

public:
    virtual void reset() = 0;

protected:
    virtual void gRender() = 0;
    virtual void _reset() = 0;

    bool should_reset;
    bool should_exit;

};

#endif // GCANVAS_H
