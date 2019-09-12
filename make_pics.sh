make

# make the leap_frog_demo
./leap_frog_demo
python plot_trajectory.py

mv trajectory.pdf onebounce.pdf pics
rm reflected.dat
rm unreflected.dat
rm onebounce.dat

rm leap_frog_demo
