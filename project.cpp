#include <iostream>
#include <vector>
#include <string>

struct User {
    std::string name;
    std::string email;
    std::string password;
    std::string batch;
    std::string enrollmentNo;
    std::string course;
    int yearOfStudy;
};

struct Ride {

    std::string from;
    std::string to;
    std::string departureTime;
    int availableSeats;
    std::vector<std::string> passengers;
};

const std::string universityLocation = "University"; // Default origin

int main() {
    std::vector<User> users; // Vector to store user data
    std::vector<Ride> rides; // Vector to store ride data

    while (true) {
        std::cout << "\nUser Registration and Ride Management System" << std::endl;
        std::cout << "1. Register a New User" << std::endl;
        std::cout << "2. Login" << std::endl;
        std::cout << "3. Create a Ride" << std::endl;
        std::cout << "4. Show All Available Rides" << std::endl;
        std::cout << "5. Search Rides by Destination" << std::endl;
        std::cout << "6. Book a Ride" << std::endl;
        std::cout << "7. Cancel a Booked Ride" << std::endl;
        std::cout << "8. Report User by Enrollment Number" << std::endl;
        std::cout << "9. Exit" << std::endl;

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
         case 1: {
               
                User user;
                std::cout << "User Registration" << std::endl;
                std::cout << "Full Name: ";
                std::cin.ignore();
                std::getline(std::cin, user.name);
                std::cout << "Email: ";
                std::cin >> user.email;
                std::cout << "Password: ";
                std::cin >> user.password;
                std::cout << "Batch: ";
                std::cin.ignore();
                std::getline(std::cin, user.batch);
                std::cout << "Enrollment Number: ";
                std::cin >> user.enrollmentNo;
                std::cout << "Course: ";
                std::cin.ignore();
                std::getline(std::cin, user.course);
                std::cout << "Year of Study: ";
                std::cin >> user.yearOfStudy;

                // Check if the email is already registered
                bool alreadyExists = false;
                for (const User& existingUser : users) {
                    if (existingUser.email == user.email) {
                        alreadyExists = true;
                        break;
                    }
                }

                if (alreadyExists) {
                    std::cout << "Error: This email is already registered." << std::endl;
                } else {
                    users.push_back(user);
                    std::cout << "Registration successful!" << std::endl;
                }

                break;
            }
         case 2: {
             
                std::string email, password;
                std::cout << "Login" << std::endl;
                std::cout << "Email: ";
                std::cin >> email;
                std::cout << "Password: ";
                std::cin >> password;

                bool loggedIn = false;
                for (const User& existingUser : users) {
                    if (existingUser.email == email && existingUser.password == password) {
                        loggedIn = true;
                        std::cout << "Login successful! Welcome, " << existingUser.name << std::endl;
                        break;
                    }
                }

                if (!loggedIn) {
                    std::cout << "Login failed. Please check your email and password." << std::endl;
                }
                break;
            }
            case 3: {
                
                if (users.empty()) {
                    std::cout << "Error: Please register and log in before creating a ride." << std::endl;
                } else {
                    Ride ride;
                    std::cout << "Create a Ride" << std::endl;
                    std::cout << "From: ";
                    std::cin.ignore();
                    std::getline(std::cin, ride.from);
                    std::cout << "To: ";
                    std::getline(std::cin, ride.to);
                    std::cout << "Departure Time: ";
                    std::getline(std::cin, ride.departureTime);
                    std::cout << "Available Seats (max 3): ";
                    std::cin >> ride.availableSeats;
                    if (ride.availableSeats > 3) {
                        std::cout << "Error: Maximum available seats is 3." << std::endl;
                    } else {
                       
                        rides.push_back(ride);
                        std::cout << "Ride created successfully!" << std::endl;
                    }
                }
              
            }
            case 4: {
                // Show all available rides with passengers
                if (rides.empty()) {
                    std::cout << "No rides available." << std::endl;
                } else {
                    std::cout << "Available Rides:" << std::endl;
                    for (int i = 0; i < rides.size(); ++i) {
                        const Ride& ride = rides[i];
                        std::cout << "Ride " << (i + 1) << ": "
                                  << "From: " << ride.from << ", To: " << ride.to
                                  << ", Departure Time: " << ride.departureTime
                                  << ", Available Seats: " << ride.availableSeats
                                 <<std::endl;
                        
                        if (!ride.passengers.empty()) {
                            std::cout << "Passengers: ";
                            for (const std::string& passenger : ride.passengers) {
                                std::cout << passenger << " ";
                            }
                            std::cout << std::endl;
                        } else {
                            std::cout << "No passengers for this ride." << std::endl;
                        }
                    }
                }
                break;
            }
            case 5: {
               std::string destination;
                std::cout << "Enter the destination: ";
                std::cin.ignore();
                std::getline(std::cin, destination);

                std::cout << "Matching Rides:" << std::endl;
                for (int i = 0; i < rides.size(); ++i) {
                    const Ride& ride = rides[i];
                    if (ride.to == destination) {
                        std::cout << "Ride " << (i + 1) << ": "
                                  << "From: " << ride.from << ", To: " << ride.to
                                  << ", Departure Time: " << ride.departureTime
                                  << ", Available Seats: " << ride.availableSeats
                                  << std::endl;
                    }
                }
                break;
            }
            case 6: {
              if (rides.empty()) {
                    std::cout << "No rides available to book." << std::endl;
                } else {
                    int rideNumber;
                    std::cout << "Enter the number of the ride you want to book: ";
                    std::cin >> rideNumber;

                    if (rideNumber > 0 && rideNumber <= rides.size()) {
                        Ride& selectedRide = rides[rideNumber - 1];
                        if (selectedRide.availableSeats > 0) {
                            selectedRide.availableSeats--;
                            std::cout << "Ride booked successfully!" << std::endl;
                        } else {
                            std::cout << "Error: This ride has no available seats." << std::endl;
                        }
                    } else {
                        std::cout << "Error: Invalid ride number." << std::endl;
                    }
                }
                break;
            }
           
            case 7: {
                if (rides.empty()) {
                    std::cout << "No rides available to cancel." << std::endl;
                } else {
                    int rideNumber;
                    std::cout << "Enter the number of the ride you want to cancel: ";
                    std::cin >> rideNumber;

                    if (rideNumber > 0 && rideNumber <= rides.size()) {
                        Ride& canceledRide = rides[rideNumber - 1];
                        // Add logic to cancel the ride, refund seats, and remove booking for the user
                        // Example: canceledRide.availableSeats += canceledRide.passengers.size();
                        //          canceledRide.passengers.clear();
                        std::cout << "Ride canceled successfully!" << std::endl;
                    } else {
                        std::cout << "Error: Invalid ride number." << std::endl;
                    }
                }
                break;
            }
            case 8: {
                // Report user by enrollment number with a reason
                std::string reportEnrollmentNo, reportReason;
                std::cout << "Enter the enrollment number of the user you want to report: ";
                std::cin >> reportEnrollmentNo;

                bool userFound = false;
                for (const User& reportedUser : users) {
                    if (reportedUser.enrollmentNo == reportEnrollmentNo) {
                        std::cout << "Enter the reason for the report: ";
                        std::cin.ignore();
                        std::getline(std::cin, reportReason);

                        std::cout << "User reported successfully: " << reportedUser.name << " (Reason: " << reportReason << ")" << std::endl;
                        userFound = true;
                        // Add logic for reporting the user with the reason
                        break;
                    }
                }

                if (!userFound) {
                    std::cout << "Error: User with enrollment number " << reportEnrollmentNo << " not found." << std::endl;
                }
                break;
            }
            case 9: {
                std::cout << "Goodbye!" << std::endl;
                return 0;
            }
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}