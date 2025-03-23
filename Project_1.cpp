#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct _capacitor
{
  double *time;       // time array
  double *voltage;    // voltage array
  double *current;    // current array
  double C;           // capacitance value
};
typedef struct _capacitor Capacitor;

void scc (Capacitor &cap, double I, double dt, int steps) {
    //function to simulate charging a capacitor with a constant current source
    for (int t = 1; t < steps; t++) {
        cap.time[t] = t * dt; //computing the time
        cap.voltage[t] = cap.voltage[t - 1] + (I * dt / cap.C);
        cap.current[t] = I; //the current then stays the same
        
        
        // gives the result every 200 timesteps
        if (t % 200 == 0) {
            cout << "Time: " << cap.time[t] << " s, Voltage: " << cap.voltage[t] << " V, Current: " << cap.current[t] << " A\n";
        }
    }
}

void scv (Capacitor &cap, double R, double V0, double dt, int steps) {
    //function to simulate charing a capacitor with a constant voltage source
    
    for (int t = 1; t < steps; t++) {
        cap.time[t] = t * dt; //computing the time again
        cap.current[t] = cap.current[t - 1] - (cap.current[t - 1] * dt / (R * cap.C));
        cap.voltage[t] = V0 - cap.current[t] * R; //computes the voltage across the capacitor
        
        //gives the results every 200 timesteps
        if (t % 200 == 0) {
            cout << "Time: " << cap.time[t] << " s, Voltage: " << cap.voltage[t] << " V, Current: " << cap.current[t] << " A\n";
        }
    }
}

int main() {
    const double dt = 1e-10; 
    const double final_time = 5e-6; 
    const int steps = static_cast<int>(final_time / dt); 
    const double R = 1000.0; 
    const double C = 100e-12;
    const double I = 1e-2;
    const double V0 = 10.0;
    
    Capacitor cap;
    //initializes the capacitor structure and allocate memory for time, voltage, and current arrays
    cap.C = C;
    cap.time = new double[steps];
    cap.voltage = new double[steps];
    cap.current = new double[steps];
    
    //initial conditions 
    cap.time[0] = 0.0;
    cap.voltage[0] = 0.0; // initial capacitor voltage is 0
    cap.current[0] = V0 / R; // initial current for constant voltage case
    
    cout << "Simulating constant current source:\n";
    scc (cap, I, dt, steps);
    
    // resets the initial conditions for constant voltage source simulation
    cout << "\nSimulating constant voltage source:\n";
    cap.voltage[0] = 0.0;
    cap.current[0] = V0 / R;
    
    // now simulate capacitor charging with a constant voltage source
    scv (cap, R, V0, dt, steps);
    
    delete[] cap.time;
    delete[] cap.voltage;
    delete[] cap.current;
    //freeing the allocated memory
    
    return 0;
}
