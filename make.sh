g++ bounding_rect.cpp -std=c++11 `pkg-config --cflags --libs opencv`
for f in *.jpg
do
	./a.out $f
	mv $f"0.jpg" ./bound_results
        mv $f"1.jpg" ./bound_results
        mv $f"2.jpg" ./bound_results
        mv $f"3.jpg" ./bound_results
        mv $f"4.jpg" ./bound_results
        mv $f"5.jpg" ./bound_results
        mv $f"6.jpg" ./bound_results
        mv $f"7.jpg" ./bound_results
        mv $f"8.jpg" ./bound_results
done
