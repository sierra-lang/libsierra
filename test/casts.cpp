#include "sierra/defines.h"

void f() {
    char                c    = 1;
    short               s    = 1;
    int                 i    = 1;
    long                l    = 1;
    long long           ll   = 1;
    unsigned char       uc   = 1;
    unsigned short      us   = 1;
    unsigned int        ui   = 1;
    unsigned long       ul   = 1;
    unsigned long long  ull  = 1;
    float               f    = 1;
    double              d    = 1;

    char                varying(4) vc    = { 1, 2, 3, 4 };
    short               varying(4) vs    = { 1, 2, 3, 4 };
    int                 varying(4) vi    = { 1, 2, 3, 4 };
    long                varying(4) vl    = { 1, 2, 3, 4 };
    long long           varying(4) vll   = { 1, 2, 3, 4 };
    unsigned char       varying(4) vuc   = { 1, 2, 3, 4 };
    unsigned short      varying(4) vus   = { 1, 2, 3, 4 };
    unsigned int        varying(4) vui   = { 1, 2, 3, 4 };
    unsigned long       varying(4) vul   = { 1, 2, 3, 4 };
    unsigned long long  varying(4) vull  = { 1, 2, 3, 4 };
    float               varying(4) vf    = { 1, 2, 3, 4 };
    double              varying(4) vd    = { 1, 2, 3, 4 };

    char                varying(4) wc    = { 1, 2, 3, 4 };
    short               varying(4) ws    = { 1, 2, 3, 4 };
    int                 varying(4) wi    = { 1, 2, 3, 4 };
    long                varying(4) wl    = { 1, 2, 3, 4 };
    long long           varying(4) wll   = { 1, 2, 3, 4 };
    unsigned char       varying(4) wuc   = { 1, 2, 3, 4 };
    unsigned short      varying(4) wus   = { 1, 2, 3, 4 };
    unsigned int        varying(4) wui   = { 1, 2, 3, 4 };
    unsigned long       varying(4) wul   = { 1, 2, 3, 4 };
    unsigned long long  varying(4) wull  = { 1, 2, 3, 4 };
    float               varying(4) wf    = { 1, 2, 3, 4 };
    double              varying(4) wd    = { 1, 2, 3, 4 };

    // assign
    vc = vc;   vs = vc;   vi = vc;   vl = vc;   vll = vc;   vuc = vc;   vus = vc;   vui = vc;   vul = vc;   vull = vc;   vf = vc;   vd = vc;  
    vc = vs;   vs = vs;   vi = vs;   vl = vs;   vll = vs;   vuc = vs;   vus = vs;   vui = vs;   vul = vs;   vull = vs;   vf = vs;   vd = vs;  
    vc = vi;   vs = vi;   vi = vi;   vl = vi;   vll = vi;   vuc = vi;   vus = vi;   vui = vi;   vul = vi;   vull = vi;   vf = vi;   vd = vi;  
    vc = vl;   vs = vl;   vi = vl;   vl = vl;   vll = vl;   vuc = vl;   vus = vl;   vui = vl;   vul = vl;   vull = vl;   vf = vl;   vd = vl;  
    vc = vll;  vs = vll;  vi = vll;  vl = vll;  vll = vll;  vuc = vll;  vus = vll;  vui = vll;  vul = vll;  vull = vll;  vf = vll;  vd = vll;  
    vc = vuc;  vs = vuc;  vi = vuc;  vl = vuc;  vll = vuc;  vuc = vuc;  vus = vuc;  vui = vuc;  vul = vuc;  vull = vuc;  vf = vuc;  vd = vuc;  
    vc = vus;  vs = vus;  vi = vus;  vl = vus;  vll = vus;  vuc = vus;  vus = vus;  vui = vus;  vul = vus;  vull = vus;  vf = vus;  vd = vus;  
    vc = vui;  vs = vui;  vi = vui;  vl = vui;  vll = vui;  vuc = vui;  vus = vui;  vui = vui;  vul = vui;  vull = vui;  vf = vui;  vd = vui;  
    vc = vul;  vs = vul;  vi = vul;  vl = vul;  vll = vul;  vuc = vul;  vus = vul;  vui = vul;  vul = vul;  vull = vul;  vf = vul;  vd = vul;  
    vc = vull; vs = vull; vi = vull; vl = vull; vll = vull; vuc = vull; vus = vull; vui = vull; vul = vull; vull = vull; vf = vull; vd = vull;  
    vc = vf;   vs = vf;   vi = vf;   vl = vf;   vll = vf;   vuc = vf;   vus = vf;   vui = vf;   vul = vf;   vull = vf;   vf = vf;   vd = vf;  
    vc = vd;   vs = vd;   vi = vd;   vl = vd;   vll = vd;   vuc = vd;   vus = vd;   vui = vd;   vul = vd;   vull = vd;   vf = vd;   vd = vd;  

    vc = c;   vs = c;   vi = c;   vl = c;   vll = c;   vuc = c;   vus = c;   vui = c;   vul = c;   vull = c;   vf = c;   vd = c;  
    vc = s;   vs = s;   vi = s;   vl = s;   vll = s;   vuc = s;   vus = s;   vui = s;   vul = s;   vull = s;   vf = s;   vd = s;  
    vc = i;   vs = i;   vi = i;   vl = i;   vll = i;   vuc = i;   vus = i;   vui = i;   vul = i;   vull = i;   vf = i;   vd = i;  
    vc = l;   vs = l;   vi = l;   vl = l;   vll = l;   vuc = l;   vus = l;   vui = l;   vul = l;   vull = l;   vf = l;   vd = l;  
    vc = ll;  vs = ll;  vi = ll;  vl = ll;  vll = ll;  vuc = ll;  vus = ll;  vui = ll;  vul = ll;  vull = ll;  vf = ll;  vd = ll;  
    vc = uc;  vs = uc;  vi = uc;  vl = uc;  vll = uc;  vuc = uc;  vus = uc;  vui = uc;  vul = uc;  vull = uc;  vf = uc;  vd = uc;  
    vc = us;  vs = us;  vi = us;  vl = us;  vll = us;  vuc = us;  vus = us;  vui = us;  vul = us;  vull = us;  vf = us;  vd = us;  
    vc = ui;  vs = ui;  vi = ui;  vl = ui;  vll = ui;  vuc = ui;  vus = ui;  vui = ui;  vul = ui;  vull = ui;  vf = ui;  vd = ui;  
    vc = ul;  vs = ul;  vi = ul;  vl = ul;  vll = ul;  vuc = ul;  vus = ul;  vui = ul;  vul = ul;  vull = ul;  vf = ul;  vd = ul;  
    vc = ull; vs = ull; vi = ull; vl = ull; vll = ull; vuc = ull; vus = ull; vui = ull; vul = ull; vull = ull; vf = ull; vd = ull;  
    vc = f;   vs = f;   vi = f;   vl = f;   vll = f;   vuc = f;   vus = f;   vui = f;   vul = f;   vull = f;   vf = f;   vd = f;  
    vc = d;   vs = d;   vi = d;   vl = d;   vll = d;   vuc = d;   vus = d;   vui = d;   vul = d;   vull = d;   vf = d;   vd = d;  

    // assign add
    vc += vc;   vs += vc;   vi += vc;   vl += vc;   vll += vc;   vuc += vc;   vus += vc;   vui += vc;   vul += vc;   vull += vc;   vf += vc;   vd += vc;  
    vc += vs;   vs += vs;   vi += vs;   vl += vs;   vll += vs;   vuc += vs;   vus += vs;   vui += vs;   vul += vs;   vull += vs;   vf += vs;   vd += vs;  
    vc += vi;   vs += vi;   vi += vi;   vl += vi;   vll += vi;   vuc += vi;   vus += vi;   vui += vi;   vul += vi;   vull += vi;   vf += vi;   vd += vi;  
    vc += vl;   vs += vl;   vi += vl;   vl += vl;   vll += vl;   vuc += vl;   vus += vl;   vui += vl;   vul += vl;   vull += vl;   vf += vl;   vd += vl;  
    vc += vll;  vs += vll;  vi += vll;  vl += vll;  vll += vll;  vuc += vll;  vus += vll;  vui += vll;  vul += vll;  vull += vll;  vf += vll;  vd += vll;  
    vc += vuc;  vs += vuc;  vi += vuc;  vl += vuc;  vll += vuc;  vuc += vuc;  vus += vuc;  vui += vuc;  vul += vuc;  vull += vuc;  vf += vuc;  vd += vuc;  
    vc += vus;  vs += vus;  vi += vus;  vl += vus;  vll += vus;  vuc += vus;  vus += vus;  vui += vus;  vul += vus;  vull += vus;  vf += vus;  vd += vus;  
    vc += vui;  vs += vui;  vi += vui;  vl += vui;  vll += vui;  vuc += vui;  vus += vui;  vui += vui;  vul += vui;  vull += vui;  vf += vui;  vd += vui;  
    vc += vul;  vs += vul;  vi += vul;  vl += vul;  vll += vul;  vuc += vul;  vus += vul;  vui += vul;  vul += vul;  vull += vul;  vf += vul;  vd += vul;  
    vc += vull; vs += vull; vi += vull; vl += vull; vll += vull; vuc += vull; vus += vull; vui += vull; vul += vull; vull += vull; vf += vull; vd += vull;  
    vc += vf;   vs += vf;   vi += vf;   vl += vf;   vll += vf;   vuc += vf;   vus += vf;   vui += vf;   vul += vf;   vull += vf;   vf += vf;   vd += vf;  
    vc += vd;   vs += vd;   vi += vd;   vl += vd;   vll += vd;   vuc += vd;   vus += vd;   vui += vd;   vul += vd;   vull += vd;   vf += vd;   vd += vd;  

    vc += c;   vs += c;   vi += c;   vl += c;   vll += c;   vuc += c;   vus += c;   vui += c;   vul += c;   vull += c;   vf += c;   vd += c;  
    vc += s;   vs += s;   vi += s;   vl += s;   vll += s;   vuc += s;   vus += s;   vui += s;   vul += s;   vull += s;   vf += s;   vd += s;  
    vc += i;   vs += i;   vi += i;   vl += i;   vll += i;   vuc += i;   vus += i;   vui += i;   vul += i;   vull += i;   vf += i;   vd += i;  
    vc += l;   vs += l;   vi += l;   vl += l;   vll += l;   vuc += l;   vus += l;   vui += l;   vul += l;   vull += l;   vf += l;   vd += l;  
    vc += ll;  vs += ll;  vi += ll;  vl += ll;  vll += ll;  vuc += ll;  vus += ll;  vui += ll;  vul += ll;  vull += ll;  vf += ll;  vd += ll;  
    vc += uc;  vs += uc;  vi += uc;  vl += uc;  vll += uc;  vuc += uc;  vus += uc;  vui += uc;  vul += uc;  vull += uc;  vf += uc;  vd += uc;  
    vc += us;  vs += us;  vi += us;  vl += us;  vll += us;  vuc += us;  vus += us;  vui += us;  vul += us;  vull += us;  vf += us;  vd += us;  
    vc += ui;  vs += ui;  vi += ui;  vl += ui;  vll += ui;  vuc += ui;  vus += ui;  vui += ui;  vul += ui;  vull += ui;  vf += ui;  vd += ui;  
    vc += ul;  vs += ul;  vi += ul;  vl += ul;  vll += ul;  vuc += ul;  vus += ul;  vui += ul;  vul += ul;  vull += ul;  vf += ul;  vd += ul;  
    vc += ull; vs += ull; vi += ull; vl += ull; vll += ull; vuc += ull; vus += ull; vui += ull; vul += ull; vull += ull; vf += ull; vd += ull;  
    vc += f;   vs += f;   vi += f;   vl += f;   vll += f;   vuc += f;   vus += f;   vui += f;   vul += f;   vull += f;   vf += f;   vd += f;  
    vc += d;   vs += d;   vi += d;   vl += d;   vll += d;   vuc += d;   vus += d;   vui += d;   vul += d;   vull += d;   vf += d;   vd += d;  

    // add
    vc + wc;   vs + wc;   vi + wc;   vl + wc;   vll + wc;   vuc + wc;   vus + wc;   vui + wc;   vul + wc;   vull + wc;   vf + wc;   vd + wc;  
    vc + ws;   vs + ws;   vi + ws;   vl + ws;   vll + ws;   vuc + ws;   vus + ws;   vui + ws;   vul + ws;   vull + ws;   vf + ws;   vd + ws;  
    vc + wi;   vs + wi;   vi + wi;   vl + wi;   vll + wi;   vuc + wi;   vus + wi;   vui + wi;   vul + wi;   vull + wi;   vf + wi;   vd + wi;  
    vc + wl;   vs + wl;   vi + wl;   vl + wl;   vll + wl;   vuc + wl;   vus + wl;   vui + wl;   vul + wl;   vull + wl;   vf + wl;   vd + wl;  
    vc + wll;  vs + wll;  vi + wll;  vl + wll;  vll + wll;  vuc + wll;  vus + wll;  vui + wll;  vul + wll;  vull + wll;  vf + wll;  vd + wll;  
    vc + wuc;  vs + wuc;  vi + wuc;  vl + wuc;  vll + wuc;  vuc + wuc;  vus + wuc;  vui + wuc;  vul + wuc;  vull + wuc;  vf + wuc;  vd + wuc;  
    vc + wus;  vs + wus;  vi + wus;  vl + wus;  vll + wus;  vuc + wus;  vus + wus;  vui + wus;  vul + wus;  vull + wus;  vf + wus;  vd + wus;  
    vc + wui;  vs + wui;  vi + wui;  vl + wui;  vll + wui;  vuc + wui;  vus + wui;  vui + wui;  vul + wui;  vull + wui;  vf + wui;  vd + wui;  
    vc + wul;  vs + wul;  vi + wul;  vl + wul;  vll + wul;  vuc + wul;  vus + wul;  vui + wul;  vul + wul;  vull + wul;  vf + wul;  vd + wul;  
    vc + wull; vs + wull; vi + wull; vl + wull; vll + wull; vuc + wull; vus + wull; vui + wull; vul + wull; vull + wull; vf + wull; vd + wull;  
    vc + wf;   vs + wf;   vi + wf;   vl + wf;   vll + wf;   vuc + wf;   vus + wf;   vui + wf;   vul + wf;   vull + wf;   vf + wf;   vd + wf;  
    vc + wd;   vs + wd;   vi + wd;   vl + wd;   vll + wd;   vuc + wd;   vus + wd;   vui + wd;   vul + wd;   vull + wd;   vf + wd;   vd + wd;  

    vc + c;   vs + c;   vi + c;   vl + c;   vll + c;   vuc + c;   vus + c;   vui + c;   vul + c;   vull + c;   vf + c;   vd + c;  
    vc + s;   vs + s;   vi + s;   vl + s;   vll + s;   vuc + s;   vus + s;   vui + s;   vul + s;   vull + s;   vf + s;   vd + s;  
    vc + i;   vs + i;   vi + i;   vl + i;   vll + i;   vuc + i;   vus + i;   vui + i;   vul + i;   vull + i;   vf + i;   vd + i;  
    vc + l;   vs + l;   vi + l;   vl + l;   vll + l;   vuc + l;   vus + l;   vui + l;   vul + l;   vull + l;   vf + l;   vd + l;  
    vc + ll;  vs + ll;  vi + ll;  vl + ll;  vll + ll;  vuc + ll;  vus + ll;  vui + ll;  vul + ll;  vull + ll;  vf + ll;  vd + ll;  
    vc + uc;  vs + uc;  vi + uc;  vl + uc;  vll + uc;  vuc + uc;  vus + uc;  vui + uc;  vul + uc;  vull + uc;  vf + uc;  vd + uc;  
    vc + us;  vs + us;  vi + us;  vl + us;  vll + us;  vuc + us;  vus + us;  vui + us;  vul + us;  vull + us;  vf + us;  vd + us;  
    vc + ui;  vs + ui;  vi + ui;  vl + ui;  vll + ui;  vuc + ui;  vus + ui;  vui + ui;  vul + ui;  vull + ui;  vf + ui;  vd + ui;  
    vc + ul;  vs + ul;  vi + ul;  vl + ul;  vll + ul;  vuc + ul;  vus + ul;  vui + ul;  vul + ul;  vull + ul;  vf + ul;  vd + ul;  
    vc + ull; vs + ull; vi + ull; vl + ull; vll + ull; vuc + ull; vus + ull; vui + ull; vul + ull; vull + ull; vf + ull; vd + ull;  
    vc + f;   vs + f;   vi + f;   vl + f;   vll + f;   vuc + f;   vus + f;   vui + f;   vul + f;   vull + f;   vf + f;   vd + f;  
    vc + d;   vs + d;   vi + d;   vl + d;   vll + d;   vuc + d;   vus + d;   vui + d;   vul + d;   vull + d;   vf + d;   vd + d;  

    c + wc;   s + wc;   i + wc;   l + wc;   ll + wc;   uc + wc;   us + wc;   ui + wc;   ul + wc;   ull + wc;   f + wc;   d + wc;  
    c + ws;   s + ws;   i + ws;   l + ws;   ll + ws;   uc + ws;   us + ws;   ui + ws;   ul + ws;   ull + ws;   f + ws;   d + ws;  
    c + wi;   s + wi;   i + wi;   l + wi;   ll + wi;   uc + wi;   us + wi;   ui + wi;   ul + wi;   ull + wi;   f + wi;   d + wi;  
    c + wl;   s + wl;   i + wl;   l + wl;   ll + wl;   uc + wl;   us + wl;   ui + wl;   ul + wl;   ull + wl;   f + wl;   d + wl;  
    c + wll;  s + wll;  i + wll;  l + wll;  ll + wll;  uc + wll;  us + wll;  ui + wll;  ul + wll;  ull + wll;  f + wll;  d + wll;  
    c + wuc;  s + wuc;  i + wuc;  l + wuc;  ll + wuc;  uc + wuc;  us + wuc;  ui + wuc;  ul + wuc;  ull + wuc;  f + wuc;  d + wuc;  
    c + wus;  s + wus;  i + wus;  l + wus;  ll + wus;  uc + wus;  us + wus;  ui + wus;  ul + wus;  ull + wus;  f + wus;  d + wus;  
    c + wui;  s + wui;  i + wui;  l + wui;  ll + wui;  uc + wui;  us + wui;  ui + wui;  ul + wui;  ull + wui;  f + wui;  d + wui;  
    c + wul;  s + wul;  i + wul;  l + wul;  ll + wul;  uc + wul;  us + wul;  ui + wul;  ul + wul;  ull + wul;  f + wul;  d + wul;  
    c + wull; s + wull; i + wull; l + wull; ll + wull; uc + wull; us + wull; ui + wull; ul + wull; ull + wull; f + wull; d + wull;  
    c + wf;   s + wf;   i + wf;   l + wf;   ll + wf;   uc + wf;   us + wf;   ui + wf;   ul + wf;   ull + wf;   f + wf;   d + wf;  
    c + wd;   s + wd;   i + wd;   l + wd;   ll + wd;   uc + wd;   us + wd;   ui + wd;   ul + wd;   ull + wd;   f + wd;   d + wd;  

    // sub
    vc - wc;   vs - wc;   vi - wc;   vl - wc;   vll - wc;   vuc - wc;   vus - wc;   vui - wc;   vul - wc;   vull - wc;   vf - wc;   vd - wc;  
    vc - ws;   vs - ws;   vi - ws;   vl - ws;   vll - ws;   vuc - ws;   vus - ws;   vui - ws;   vul - ws;   vull - ws;   vf - ws;   vd - ws;  
    vc - wi;   vs - wi;   vi - wi;   vl - wi;   vll - wi;   vuc - wi;   vus - wi;   vui - wi;   vul - wi;   vull - wi;   vf - wi;   vd - wi;  
    vc - wl;   vs - wl;   vi - wl;   vl - wl;   vll - wl;   vuc - wl;   vus - wl;   vui - wl;   vul - wl;   vull - wl;   vf - wl;   vd - wl;  
    vc - wll;  vs - wll;  vi - wll;  vl - wll;  vll - wll;  vuc - wll;  vus - wll;  vui - wll;  vul - wll;  vull - wll;  vf - wll;  vd - wll;  
    vc - wuc;  vs - wuc;  vi - wuc;  vl - wuc;  vll - wuc;  vuc - wuc;  vus - wuc;  vui - wuc;  vul - wuc;  vull - wuc;  vf - wuc;  vd - wuc;  
    vc - wus;  vs - wus;  vi - wus;  vl - wus;  vll - wus;  vuc - wus;  vus - wus;  vui - wus;  vul - wus;  vull - wus;  vf - wus;  vd - wus;  
    vc - wui;  vs - wui;  vi - wui;  vl - wui;  vll - wui;  vuc - wui;  vus - wui;  vui - wui;  vul - wui;  vull - wui;  vf - wui;  vd - wui;  
    vc - wul;  vs - wul;  vi - wul;  vl - wul;  vll - wul;  vuc - wul;  vus - wul;  vui - wul;  vul - wul;  vull - wul;  vf - wul;  vd - wul;  
    vc - wull; vs - wull; vi - wull; vl - wull; vll - wull; vuc - wull; vus - wull; vui - wull; vul - wull; vull - wull; vf - wull; vd - wull;  
    vc - wf;   vs - wf;   vi - wf;   vl - wf;   vll - wf;   vuc - wf;   vus - wf;   vui - wf;   vul - wf;   vull - wf;   vf - wf;   vd - wf;  
    vc - wd;   vs - wd;   vi - wd;   vl - wd;   vll - wd;   vuc - wd;   vus - wd;   vui - wd;   vul - wd;   vull - wd;   vf - wd;   vd - wd;  

    vc - c;   vs - c;   vi - c;   vl - c;   vll - c;   vuc - c;   vus - c;   vui - c;   vul - c;   vull - c;   vf - c;   vd - c;  
    vc - s;   vs - s;   vi - s;   vl - s;   vll - s;   vuc - s;   vus - s;   vui - s;   vul - s;   vull - s;   vf - s;   vd - s;  
    vc - i;   vs - i;   vi - i;   vl - i;   vll - i;   vuc - i;   vus - i;   vui - i;   vul - i;   vull - i;   vf - i;   vd - i;  
    vc - l;   vs - l;   vi - l;   vl - l;   vll - l;   vuc - l;   vus - l;   vui - l;   vul - l;   vull - l;   vf - l;   vd - l;  
    vc - ll;  vs - ll;  vi - ll;  vl - ll;  vll - ll;  vuc - ll;  vus - ll;  vui - ll;  vul - ll;  vull - ll;  vf - ll;  vd - ll;  
    vc - uc;  vs - uc;  vi - uc;  vl - uc;  vll - uc;  vuc - uc;  vus - uc;  vui - uc;  vul - uc;  vull - uc;  vf - uc;  vd - uc;  
    vc - us;  vs - us;  vi - us;  vl - us;  vll - us;  vuc - us;  vus - us;  vui - us;  vul - us;  vull - us;  vf - us;  vd - us;  
    vc - ui;  vs - ui;  vi - ui;  vl - ui;  vll - ui;  vuc - ui;  vus - ui;  vui - ui;  vul - ui;  vull - ui;  vf - ui;  vd - ui;  
    vc - ul;  vs - ul;  vi - ul;  vl - ul;  vll - ul;  vuc - ul;  vus - ul;  vui - ul;  vul - ul;  vull - ul;  vf - ul;  vd - ul;  
    vc - ull; vs - ull; vi - ull; vl - ull; vll - ull; vuc - ull; vus - ull; vui - ull; vul - ull; vull - ull; vf - ull; vd - ull;  
    vc - f;   vs - f;   vi - f;   vl - f;   vll - f;   vuc - f;   vus - f;   vui - f;   vul - f;   vull - f;   vf - f;   vd - f;  
    vc - d;   vs - d;   vi - d;   vl - d;   vll - d;   vuc - d;   vus - d;   vui - d;   vul - d;   vull - d;   vf - d;   vd - d;  

    c - wc;   s - wc;   i - wc;   l - wc;   ll - wc;   uc - wc;   us - wc;   ui - wc;   ul - wc;   ull - wc;   f - wc;   d - wc;  
    c - ws;   s - ws;   i - ws;   l - ws;   ll - ws;   uc - ws;   us - ws;   ui - ws;   ul - ws;   ull - ws;   f - ws;   d - ws;  
    c - wi;   s - wi;   i - wi;   l - wi;   ll - wi;   uc - wi;   us - wi;   ui - wi;   ul - wi;   ull - wi;   f - wi;   d - wi;  
    c - wl;   s - wl;   i - wl;   l - wl;   ll - wl;   uc - wl;   us - wl;   ui - wl;   ul - wl;   ull - wl;   f - wl;   d - wl;  
    c - wll;  s - wll;  i - wll;  l - wll;  ll - wll;  uc - wll;  us - wll;  ui - wll;  ul - wll;  ull - wll;  f - wll;  d - wll;  
    c - wuc;  s - wuc;  i - wuc;  l - wuc;  ll - wuc;  uc - wuc;  us - wuc;  ui - wuc;  ul - wuc;  ull - wuc;  f - wuc;  d - wuc;  
    c - wus;  s - wus;  i - wus;  l - wus;  ll - wus;  uc - wus;  us - wus;  ui - wus;  ul - wus;  ull - wus;  f - wus;  d - wus;  
    c - wui;  s - wui;  i - wui;  l - wui;  ll - wui;  uc - wui;  us - wui;  ui - wui;  ul - wui;  ull - wui;  f - wui;  d - wui;  
    c - wul;  s - wul;  i - wul;  l - wul;  ll - wul;  uc - wul;  us - wul;  ui - wul;  ul - wul;  ull - wul;  f - wul;  d - wul;  
    c - wull; s - wull; i - wull; l - wull; ll - wull; uc - wull; us - wull; ui - wull; ul - wull; ull - wull; f - wull; d - wull;  
    c - wf;   s - wf;   i - wf;   l - wf;   ll - wf;   uc - wf;   us - wf;   ui - wf;   ul - wf;   ull - wf;   f - wf;   d - wf;  
    c - wd;   s - wd;   i - wd;   l - wd;   ll - wd;   uc - wd;   us - wd;   ui - wd;   ul - wd;   ull - wd;   f - wd;   d - wd;  

    // mul
    vc * wc;   vs * wc;   vi * wc;   vl * wc;   vll * wc;   vuc * wc;   vus * wc;   vui * wc;   vul * wc;   vull * wc;   vf * wc;   vd * wc;  
    vc * ws;   vs * ws;   vi * ws;   vl * ws;   vll * ws;   vuc * ws;   vus * ws;   vui * ws;   vul * ws;   vull * ws;   vf * ws;   vd * ws;  
    vc * wi;   vs * wi;   vi * wi;   vl * wi;   vll * wi;   vuc * wi;   vus * wi;   vui * wi;   vul * wi;   vull * wi;   vf * wi;   vd * wi;  
    vc * wl;   vs * wl;   vi * wl;   vl * wl;   vll * wl;   vuc * wl;   vus * wl;   vui * wl;   vul * wl;   vull * wl;   vf * wl;   vd * wl;  
    vc * wll;  vs * wll;  vi * wll;  vl * wll;  vll * wll;  vuc * wll;  vus * wll;  vui * wll;  vul * wll;  vull * wll;  vf * wll;  vd * wll;  
    vc * wuc;  vs * wuc;  vi * wuc;  vl * wuc;  vll * wuc;  vuc * wuc;  vus * wuc;  vui * wuc;  vul * wuc;  vull * wuc;  vf * wuc;  vd * wuc;  
    vc * wus;  vs * wus;  vi * wus;  vl * wus;  vll * wus;  vuc * wus;  vus * wus;  vui * wus;  vul * wus;  vull * wus;  vf * wus;  vd * wus;  
    vc * wui;  vs * wui;  vi * wui;  vl * wui;  vll * wui;  vuc * wui;  vus * wui;  vui * wui;  vul * wui;  vull * wui;  vf * wui;  vd * wui;  
    vc * wul;  vs * wul;  vi * wul;  vl * wul;  vll * wul;  vuc * wul;  vus * wul;  vui * wul;  vul * wul;  vull * wul;  vf * wul;  vd * wul;  
    vc * wull; vs * wull; vi * wull; vl * wull; vll * wull; vuc * wull; vus * wull; vui * wull; vul * wull; vull * wull; vf * wull; vd * wull;  
    vc * wf;   vs * wf;   vi * wf;   vl * wf;   vll * wf;   vuc * wf;   vus * wf;   vui * wf;   vul * wf;   vull * wf;   vf * wf;   vd * wf;  
    vc * wd;   vs * wd;   vi * wd;   vl * wd;   vll * wd;   vuc * wd;   vus * wd;   vui * wd;   vul * wd;   vull * wd;   vf * wd;   vd * wd;  

    vc * c;   vs * c;   vi * c;   vl * c;   vll * c;   vuc * c;   vus * c;   vui * c;   vul * c;   vull * c;   vf * c;   vd * c;  
    vc * s;   vs * s;   vi * s;   vl * s;   vll * s;   vuc * s;   vus * s;   vui * s;   vul * s;   vull * s;   vf * s;   vd * s;  
    vc * i;   vs * i;   vi * i;   vl * i;   vll * i;   vuc * i;   vus * i;   vui * i;   vul * i;   vull * i;   vf * i;   vd * i;  
    vc * l;   vs * l;   vi * l;   vl * l;   vll * l;   vuc * l;   vus * l;   vui * l;   vul * l;   vull * l;   vf * l;   vd * l;  
    vc * ll;  vs * ll;  vi * ll;  vl * ll;  vll * ll;  vuc * ll;  vus * ll;  vui * ll;  vul * ll;  vull * ll;  vf * ll;  vd * ll;  
    vc * uc;  vs * uc;  vi * uc;  vl * uc;  vll * uc;  vuc * uc;  vus * uc;  vui * uc;  vul * uc;  vull * uc;  vf * uc;  vd * uc;  
    vc * us;  vs * us;  vi * us;  vl * us;  vll * us;  vuc * us;  vus * us;  vui * us;  vul * us;  vull * us;  vf * us;  vd * us;  
    vc * ui;  vs * ui;  vi * ui;  vl * ui;  vll * ui;  vuc * ui;  vus * ui;  vui * ui;  vul * ui;  vull * ui;  vf * ui;  vd * ui;  
    vc * ul;  vs * ul;  vi * ul;  vl * ul;  vll * ul;  vuc * ul;  vus * ul;  vui * ul;  vul * ul;  vull * ul;  vf * ul;  vd * ul;  
    vc * ull; vs * ull; vi * ull; vl * ull; vll * ull; vuc * ull; vus * ull; vui * ull; vul * ull; vull * ull; vf * ull; vd * ull;  
    vc * f;   vs * f;   vi * f;   vl * f;   vll * f;   vuc * f;   vus * f;   vui * f;   vul * f;   vull * f;   vf * f;   vd * f;  
    vc * d;   vs * d;   vi * d;   vl * d;   vll * d;   vuc * d;   vus * d;   vui * d;   vul * d;   vull * d;   vf * d;   vd * d;  

    c * wc;   s * wc;   i * wc;   l * wc;   ll * wc;   uc * wc;   us * wc;   ui * wc;   ul * wc;   ull * wc;   f * wc;   d * wc;  
    c * ws;   s * ws;   i * ws;   l * ws;   ll * ws;   uc * ws;   us * ws;   ui * ws;   ul * ws;   ull * ws;   f * ws;   d * ws;  
    c * wi;   s * wi;   i * wi;   l * wi;   ll * wi;   uc * wi;   us * wi;   ui * wi;   ul * wi;   ull * wi;   f * wi;   d * wi;  
    c * wl;   s * wl;   i * wl;   l * wl;   ll * wl;   uc * wl;   us * wl;   ui * wl;   ul * wl;   ull * wl;   f * wl;   d * wl;  
    c * wll;  s * wll;  i * wll;  l * wll;  ll * wll;  uc * wll;  us * wll;  ui * wll;  ul * wll;  ull * wll;  f * wll;  d * wll;  
    c * wuc;  s * wuc;  i * wuc;  l * wuc;  ll * wuc;  uc * wuc;  us * wuc;  ui * wuc;  ul * wuc;  ull * wuc;  f * wuc;  d * wuc;  
    c * wus;  s * wus;  i * wus;  l * wus;  ll * wus;  uc * wus;  us * wus;  ui * wus;  ul * wus;  ull * wus;  f * wus;  d * wus;  
    c * wui;  s * wui;  i * wui;  l * wui;  ll * wui;  uc * wui;  us * wui;  ui * wui;  ul * wui;  ull * wui;  f * wui;  d * wui;  
    c * wul;  s * wul;  i * wul;  l * wul;  ll * wul;  uc * wul;  us * wul;  ui * wul;  ul * wul;  ull * wul;  f * wul;  d * wul;  
    c * wull; s * wull; i * wull; l * wull; ll * wull; uc * wull; us * wull; ui * wull; ul * wull; ull * wull; f * wull; d * wull;  
    c * wf;   s * wf;   i * wf;   l * wf;   ll * wf;   uc * wf;   us * wf;   ui * wf;   ul * wf;   ull * wf;   f * wf;   d * wf;  
    c * wd;   s * wd;   i * wd;   l * wd;   ll * wd;   uc * wd;   us * wd;   ui * wd;   ul * wd;   ull * wd;   f * wd;   d * wd;  

    // div
    vc / wc;   vs / wc;   vi / wc;   vl / wc;   vll / wc;   vuc / wc;   vus / wc;   vui / wc;   vul / wc;   vull / wc;   vf / wc;   vd / wc;  
    vc / ws;   vs / ws;   vi / ws;   vl / ws;   vll / ws;   vuc / ws;   vus / ws;   vui / ws;   vul / ws;   vull / ws;   vf / ws;   vd / ws;  
    vc / wi;   vs / wi;   vi / wi;   vl / wi;   vll / wi;   vuc / wi;   vus / wi;   vui / wi;   vul / wi;   vull / wi;   vf / wi;   vd / wi;  
    vc / wl;   vs / wl;   vi / wl;   vl / wl;   vll / wl;   vuc / wl;   vus / wl;   vui / wl;   vul / wl;   vull / wl;   vf / wl;   vd / wl;  
    vc / wll;  vs / wll;  vi / wll;  vl / wll;  vll / wll;  vuc / wll;  vus / wll;  vui / wll;  vul / wll;  vull / wll;  vf / wll;  vd / wll;  
    vc / wuc;  vs / wuc;  vi / wuc;  vl / wuc;  vll / wuc;  vuc / wuc;  vus / wuc;  vui / wuc;  vul / wuc;  vull / wuc;  vf / wuc;  vd / wuc;  
    vc / wus;  vs / wus;  vi / wus;  vl / wus;  vll / wus;  vuc / wus;  vus / wus;  vui / wus;  vul / wus;  vull / wus;  vf / wus;  vd / wus;  
    vc / wui;  vs / wui;  vi / wui;  vl / wui;  vll / wui;  vuc / wui;  vus / wui;  vui / wui;  vul / wui;  vull / wui;  vf / wui;  vd / wui;  
    vc / wul;  vs / wul;  vi / wul;  vl / wul;  vll / wul;  vuc / wul;  vus / wul;  vui / wul;  vul / wul;  vull / wul;  vf / wul;  vd / wul;  
    vc / wull; vs / wull; vi / wull; vl / wull; vll / wull; vuc / wull; vus / wull; vui / wull; vul / wull; vull / wull; vf / wull; vd / wull;  
    vc / wf;   vs / wf;   vi / wf;   vl / wf;   vll / wf;   vuc / wf;   vus / wf;   vui / wf;   vul / wf;   vull / wf;   vf / wf;   vd / wf;  
    vc / wd;   vs / wd;   vi / wd;   vl / wd;   vll / wd;   vuc / wd;   vus / wd;   vui / wd;   vul / wd;   vull / wd;   vf / wd;   vd / wd;  

    vc / c;   vs / c;   vi / c;   vl / c;   vll / c;   vuc / c;   vus / c;   vui / c;   vul / c;   vull / c;   vf / c;   vd / c;  
    vc / s;   vs / s;   vi / s;   vl / s;   vll / s;   vuc / s;   vus / s;   vui / s;   vul / s;   vull / s;   vf / s;   vd / s;  
    vc / i;   vs / i;   vi / i;   vl / i;   vll / i;   vuc / i;   vus / i;   vui / i;   vul / i;   vull / i;   vf / i;   vd / i;  
    vc / l;   vs / l;   vi / l;   vl / l;   vll / l;   vuc / l;   vus / l;   vui / l;   vul / l;   vull / l;   vf / l;   vd / l;  
    vc / ll;  vs / ll;  vi / ll;  vl / ll;  vll / ll;  vuc / ll;  vus / ll;  vui / ll;  vul / ll;  vull / ll;  vf / ll;  vd / ll;  
    vc / uc;  vs / uc;  vi / uc;  vl / uc;  vll / uc;  vuc / uc;  vus / uc;  vui / uc;  vul / uc;  vull / uc;  vf / uc;  vd / uc;  
    vc / us;  vs / us;  vi / us;  vl / us;  vll / us;  vuc / us;  vus / us;  vui / us;  vul / us;  vull / us;  vf / us;  vd / us;  
    vc / ui;  vs / ui;  vi / ui;  vl / ui;  vll / ui;  vuc / ui;  vus / ui;  vui / ui;  vul / ui;  vull / ui;  vf / ui;  vd / ui;  
    vc / ul;  vs / ul;  vi / ul;  vl / ul;  vll / ul;  vuc / ul;  vus / ul;  vui / ul;  vul / ul;  vull / ul;  vf / ul;  vd / ul;  
    vc / ull; vs / ull; vi / ull; vl / ull; vll / ull; vuc / ull; vus / ull; vui / ull; vul / ull; vull / ull; vf / ull; vd / ull;  
    vc / f;   vs / f;   vi / f;   vl / f;   vll / f;   vuc / f;   vus / f;   vui / f;   vul / f;   vull / f;   vf / f;   vd / f;  
    vc / d;   vs / d;   vi / d;   vl / d;   vll / d;   vuc / d;   vus / d;   vui / d;   vul / d;   vull / d;   vf / d;   vd / d;  

    c / wc;   s / wc;   i / wc;   l / wc;   ll / wc;   uc / wc;   us / wc;   ui / wc;   ul / wc;   ull / wc;   f / wc;   d / wc;  
    c / ws;   s / ws;   i / ws;   l / ws;   ll / ws;   uc / ws;   us / ws;   ui / ws;   ul / ws;   ull / ws;   f / ws;   d / ws;  
    c / wi;   s / wi;   i / wi;   l / wi;   ll / wi;   uc / wi;   us / wi;   ui / wi;   ul / wi;   ull / wi;   f / wi;   d / wi;  
    c / wl;   s / wl;   i / wl;   l / wl;   ll / wl;   uc / wl;   us / wl;   ui / wl;   ul / wl;   ull / wl;   f / wl;   d / wl;  
    c / wll;  s / wll;  i / wll;  l / wll;  ll / wll;  uc / wll;  us / wll;  ui / wll;  ul / wll;  ull / wll;  f / wll;  d / wll;  
    c / wuc;  s / wuc;  i / wuc;  l / wuc;  ll / wuc;  uc / wuc;  us / wuc;  ui / wuc;  ul / wuc;  ull / wuc;  f / wuc;  d / wuc;  
    c / wus;  s / wus;  i / wus;  l / wus;  ll / wus;  uc / wus;  us / wus;  ui / wus;  ul / wus;  ull / wus;  f / wus;  d / wus;  
    c / wui;  s / wui;  i / wui;  l / wui;  ll / wui;  uc / wui;  us / wui;  ui / wui;  ul / wui;  ull / wui;  f / wui;  d / wui;  
    c / wul;  s / wul;  i / wul;  l / wul;  ll / wul;  uc / wul;  us / wul;  ui / wul;  ul / wul;  ull / wul;  f / wul;  d / wul;  
    c / wull; s / wull; i / wull; l / wull; ll / wull; uc / wull; us / wull; ui / wull; ul / wull; ull / wull; f / wull; d / wull;  
    c / wf;   s / wf;   i / wf;   l / wf;   ll / wf;   uc / wf;   us / wf;   ui / wf;   ul / wf;   ull / wf;   f / wf;   d / wf;  
    c / wd;   s / wd;   i / wd;   l / wd;   ll / wd;   uc / wd;   us / wd;   ui / wd;   ul / wd;   ull / wd;   f / wd;   d / wd;  
}
