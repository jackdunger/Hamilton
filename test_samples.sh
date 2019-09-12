# (set -x;
#  g++ --std=c++11 test.cpp Random.cpp LeapFrog.cpp -I. -o test
# ./test > samples.dat
# python show_samples.py
# rm test
# rm samples.dat
# mv samples_test.pdf pics
# imgcat pics/samples_test.pdf
# )

(set -x;
 g++ --std=c++11 test2.cpp Random.cpp LeapFrog.cpp -I. -o test2
./test2 > samples.dat
python show_samples2.py
rm test2
rm samples.dat
mv samples_test2.pdf pics
imgcat pics/samples_test2.pdf
)
