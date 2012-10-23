#include <math.h>
#include <iostream>
using namespace std;

double getMaxNuts(double N, double D, double C, double F) {

	// base case:
	// We have the capacity to carry all nuts,
	// so fetch all the nuts in one trip
	if (N <= C) {
		double nutsAtDestination = N - D*F;
		return (nutsAtDestination >= 0.0) ?
			nutsAtDestination :
			0.0;    // out of fuel!
	}
	// # trips you would travel back and forth
	int numTrips = 2*(ceil(N/C) - 1) + 1;
	// how many nuts you consume per km
	double costPerKm = numTrips * F;
	// remaining weight of nuts after consumption
	double remainingNuts = C*(ceil(N/C) - 1.0);
	// this is the distance you are able to travel before you
	// reach ONE LESS round trip fetching nuts
	// derived from eq: N - costPerKm * traveled = remainingNuts
	double traveled = (N - remainingNuts) / costPerKm;
	// we are able to travel greater (or equal) than the remaining
	// distance, so fetch the nuts right to the destination
	if (traveled >= D)
		return N - D*costPerKm;

	// calculate recursively as we travel ONE less round trip now.
	return getMaxNuts(remainingNuts, D-traveled, C, F);

}


int main()
{
	cout<<getMaxNuts(100, 20, 50, 1);
	return 0;
}
