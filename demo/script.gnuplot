set terminal wxt size 800,800;
set title 'Sierra';
set xlabel 'Mandelbrot';
set ylabel 'Time (million cycles)';
set yrange [0:800];
set xrange [-.5:*];
set boxwidth 0.75;
set style line 1 lc rgb "red"
set style line 2 lc rgb "green"
set style line 3 lc rgb "blue"
unset key;
set grid;
set grid noxtics nomxtics ytics nomytics noztics nomztics nox2tics nomx2tics noy2tics nomy2tics nocbtics nomcbtics;
set style fill solid 1.0 border -1; 
set xtics border in scale 0,10 nomirror;
plot 'data' every ::0::0 using 1:2:xticlabels(3) w boxes ls 1, \
     'data' every ::1::1 using 1:2:xticlabels(3) w boxes ls 2, \
     'data' every ::2::2 using 1:2:xticlabels(3) w boxes ls 3;
