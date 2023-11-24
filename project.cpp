#include <iostream>
#include <vector>
#include <string>
#include <map>

class Profile {
public:
    std::string role;
    std::string year;
    std::string course;
    std::string batch;

    Profile(const std::string& userRole, const std::string& userYear, const std::string& userCourse, const std::string& userBatch)
        : role(userRole), year(userYear), course(userCourse), batch(userBatch) {}
};

class User {
public:
    std::string name;
    std::string email;
    std::string password;
    std::string batch;
    std::string enrollmentNo;
    std::string course;
    int yearOfStudy;
    Profile profile;
    int currentRideIndex;

    User(const std::string& userName, const std::string& userEmail, const std::string& userPassword,
         const std::string& userBatch, const std::string& userEnrollmentNo, const std::string& userCourse,
         int userYearOfStudy, const Profile& userProfile)
        : name(userName), email(userEmail), password(userPassword), batch(userBatch),
          enrollmentNo(userEnrollmentNo), course(userCourse), yearOfStudy(userYearOfStudy), profile(userProfile) {}
};

class Ride {
public:
    std::string from;
    std::string to;
    std::string departureTime;
    int availableSeats;
    std::vector<std::string> passengers;
    bool isCompleted;

    Ride() : isCompleted(false) {}
};

class CarpoolRequest {
public:
    std::string location;
    std::string time;
    std::string date;
    int vehicleType;  // 2 or 4 persons

    CarpoolRequest(const std::string& loc, const std::string& t, const std::string& d, int type)
        : location(loc), time(t), date(d), vehicleType(type) {}
};

class CarpoolSystem {
public:
    std::vector<User> users;
    std::vector<Ride> rides;
    std::map<std::string, std::vector<int>> bookedRides; // Map user email to booked ride indices
    std::vector<CarpoolRequest> carpoolRequests;
};

const std::string universityLocation = "University"; // Default origin

class CarpoolApp {
private:
    CarpoolSystem carpoolSystem;
    User* currentUser;

public:
    CarpoolApp() : currentUser(nullptr) {}

    void signUp() {
    std::string userName, userEmail, userPassword, userCourse, userBatch, userEnrollmentNo;
    int userYearOfStudy;

    std::cout << "User Registration" << std::endl;
    std::cin.ignore(); // Clear the input buffer
    std::cout << "Full Name: ";
    std::getline(std::cin, userName);
    std::cout << "Email: ";
    std::cin >> userEmail;
    std::cout << "Password: ";
    std::cin >> userPassword;
    std::cout << "Course: ";
    std::cin.ignore();
    std::getline(std::cin, userCourse);
    std::cout << "Year of Study: ";
    std::cin >> userYearOfStudy;
    std::cout << "Batch: ";
    std::cin.ignore();
    std::getline(std::cin, userBatch);
    std::cout << "Enrollment Number: ";
    std::cin >> userEnrollmentNo;

    Profile userProfile("student", std::to_string(userYearOfStudy), userCourse, userBatch);
    carpoolSystem.users.push_back(User(userName, userEmail, userPassword, userBatch,
                                       userEnrollmentNo, userCourse, userYearOfStudy, userProfile));

    std::cout << "Registration successful!" << std::endl;
}

    void login() {
        std::string email, password;
        std::cout << "Login" << std::endl;
        std::cout << "Email: ";
        std::cin >> email;
        std::cout << "Password: ";
        std::cin >> password;

        bool loggedIn = false;
        for (User& existingUser : carpoolSystem.users) {
            if (existingUser.email == email && existingUser.password == password) {
                loggedIn = true;
                currentUser = &existingUser;
                std::cout << "Login successful! Welcome, " << currentUser->name << std::endl;
                break;
            }
        }

        if (!loggedIn) {
            std::cout << "Login failed. Please check your email and password." << std::endl;
        }
    }

    void logout() {
        currentUser = nullptr;
        std::cout << "Logout successful. Goodbye!" << std::endl;
    }

    void carpool() {
        if (currentUser == nullptr) {
            std::cout << "Error: Please login before accessing carpool features." << std::endl;
            return;
        }

        int option;
        do {
        std::cout << "====== Carpool Menu ======" << std::endl;
        std::cout << "1. Offer a Carpool" << std::endl;
        std::cout << "2. View Carpool Requests" << std::endl;
        std::cout << "3. Match Carpool Requests" << std::endl;
        std::cout << "4. Accept a Ride" << std::endl;
        std::cout << "5. Mark Ride as Completed" << std::endl;
        std::cout << "6. Cancel Ride" << std::endl;
        std::cout << "7. Report User" << std::endl;  // New option for reporting a user
        std::cout << "8. Logout" << std::endl;
        std::cout << "===========================" << std::endl;
        std::cout << "Enter your option (1-8): ";
        std::cin >> option;

        switch (option) {
            case 1:
                offerCarpool();
                break;
            case 2:
                viewCarpoolRequests();
                break;
            case 3:
                matchCarpoolRequests();
                break;
            case 4:
                acceptRide();
                break;
            case 5:
                markRideAsCompleted();
                break;
            case 6:
                cancelRide();
                break;
            case 7:
                reportUser();
                break;  // New case for reporting a user
            case 8:
                logout();
                return;
            default:
                std::cout << "Invalid option. Please enter a number between 1 and 8." << std::endl;
        }

    } while (option != 8);
    }

private:
    void offerCarpool() {
        Ride ride;
        std::cout << "Create a Ride" << std::endl;
        std::cout << "From: ";
        std::cin.ignore();
        std::getline(std::cin, ride.from);
        std::cout << "To: ";
        std::getline(std::cin, ride.to);
        std::cout << "Departure Time: ";
        std::getline(std::cin, ride.departureTime);
        std::cout << "Available Seats (max 4): ";
        std::cin >> ride.availableSeats;

        if (ride.availableSeats > 4) {
            std::cout << "Error: Maximum available seats is 4." << std::endl;
        } else {
            ride.passengers.push_back(currentUser->email); // Add the ride creator as the first passenger
            carpoolSystem.rides.push_back(ride);
            std::cout << "Ride created successfully!" << std::endl;
        }
    }

    void viewCarpoolRequests() {
        std::cout << "All carpool requests:" << std::endl;
    for (const auto& request : carpoolSystem.carpoolRequests) {
        std::cout << "Location: " << request.location << ", Date: " << request.date
                  << ", Time: " << request.time << ", Vehicle Type: " << request.vehicleType << std::endl;
    }

    if (!carpoolSystem.rides.empty()) {
        std::cout << "Available Rides:" << std::endl;
        for (int i = 0; i < carpoolSystem.rides.size(); ++i) {
            const Ride& ride = carpoolSystem.rides[i];
            std::cout << (i + 1) << ". From: " << ride.from << ", To: " << ride.to
                      << ", Departure Time: " << ride.departureTime
                      << ", Available Seats: " << ride.availableSeats
                      << std::endl;
        }
    }
    }

    void matchCarpoolRequests() {
        if (carpoolSystem.carpoolRequests.size() < 2) {
            std::cout << "Not enough carpool requests to match." << std::endl;
            return;
        }

        // Assume currentUser's carpool request is at index 0
        CarpoolRequest currentUserRequest = carpoolSystem.carpoolRequests[0];

        for (size_t i = 1; i < carpoolSystem.carpoolRequests.size(); ++i) {
            CarpoolRequest otherRequest = carpoolSystem.carpoolRequests[i];

            if (areRequestsCompatible(currentUserRequest, otherRequest)) {
                std::cout << "Compatible carpool found!" << std::endl;
                displayCarpoolMatch(currentUserRequest, otherRequest);
            }
        }
    }

    void acceptRide() {
        if (carpoolSystem.rides.empty()) {
        std::cout << "No rides available to accept." << std::endl;
        return;
    }

    // Show available rides
    std::cout << "Available Rides:" << std::endl;
    for (int i = 0; i < carpoolSystem.rides.size(); ++i) {
        const Ride& ride = carpoolSystem.rides[i];
        std::cout << (i + 1) << ". From: " << ride.from << ", To: " << ride.to
                  << ", Departure Time: " << ride.departureTime
                  << ", Available Seats: " << ride.availableSeats
                  << std::endl;
    }

    int rideNumber;
    std::cout << "Enter the number of the ride you want to accept: ";
    std::cin >> rideNumber;

    if (rideNumber > 0 && rideNumber <= carpoolSystem.rides.size()) {
        Ride& selectedRide = carpoolSystem.rides[rideNumber - 1];
        if (selectedRide.availableSeats > 0) {
            selectedRide.availableSeats--;
            carpoolSystem.bookedRides[currentUser->email].push_back(rideNumber - 1); // Book the ride for the user
            std::cout << "Ride accepted successfully!" << std::endl;

            // Display the details of the accepted ride
            std::cout << "Accepted Ride Details:" << std::endl;
            std::cout << "From: " << selectedRide.from << ", To: " << selectedRide.to
                      << ", Departure Time: " << selectedRide.departureTime
                      << ", Available Seats: " << selectedRide.availableSeats
                      << std::endl;
        } else {
            std::cout << "Error: This ride has no available seats." << std::endl;
        }
    } else {
        std::cout << "Error: Invalid ride number." << std::endl;
    }
    }

    void markRideAsCompleted() {
        if (carpoolSystem.rides.empty()) {
            std::cout << "No rides available to mark as completed." << std::endl;
            return;
        }

        int rideNumber;
        std::cout << "Enter the number of the ride you want to mark as completed: ";
        std::cin >> rideNumber;

        if (rideNumber > 0 && rideNumber <= carpoolSystem.rides.size()) {
            Ride& selectedRide = carpoolSystem.rides[rideNumber - 1];
            if (!selectedRide.isCompleted) {
                selectedRide.isCompleted = true;
                std::cout << "Ride marked as completed successfully!" << std::endl;
            } else {
                std::cout << "Error: This ride has already been marked as completed." << std::endl;
            }
        } else {
            std::cout << "Error: Invalid ride number." << std::endl;
        }
    }

    bool areRequestsCompatible(const CarpoolRequest& request1, const CarpoolRequest& request2) {
        // Check compatibility criteria (add your own logic)
        return (request1.location == request2.location &&
                request1.date == request2.date &&
                request1.time == request2.time &&
                request1.vehicleType == request2.vehicleType);
    }

    void displayCarpoolMatch(const CarpoolRequest& request1, const CarpoolRequest& request2) {
        std::cout << "Matched Carpool Requests:" << std::endl;
        std::cout << "User 1 - Location: " << request1.location << ", Date: " << request1.date
                  << ", Time: " << request1.time << ", Vehicle Type: " << request1.vehicleType << std::endl;

        std::cout << "User 2 - Location: " << request2.location << ", Date: " << request2.date
                  << ", Time: " << request2.time << ", Vehicle Type: " << request2.vehicleType << std::endl;
    }
    void cancelRide() {
        if (currentUser == nullptr) {
            std::cout << "Error: Please login before accessing carpool features." << std::endl;
            return;
        }

        if (currentUser->currentRideIndex != -1) {
            Ride& currentRide = carpoolSystem.rides[currentUser->currentRideIndex];
            std::cout << "Cancelling your current ride..." << std::endl;
            currentRide.availableSeats += currentRide.passengers.size(); // Add back the booked seats
            currentRide.passengers.clear(); // Remove all passengers
            currentUser->currentRideIndex = -1; // Set user's current ride index to -1
            std::cout << "Ride cancelled successfully!" << std::endl;
        } else {
            std::cout << "You do not have a current ride to cancel." << std::endl;
        }
    }
    void reportUser() {
        if (currentUser == nullptr) {
            std::cout << "Error: Please login before accessing carpool features." << std::endl;
            return;
        }

        std::string reportedEmail, reason;
        std::cout << "Enter the email of the user you want to report: ";
        std::cin >> reportedEmail;

        // You can also prompt the user for a reason for reporting
        std::cout << "Enter the reason for reporting: ";
        std::cin.ignore();
        std::getline(std::cin, reason);

        // Implement your logic to handle the user report here
        // For example, you might add the report to a list or take appropriate actions
        // You can also provide feedback to the user that the report has been submitted

        std::cout << "User reported successfully!" << std::endl;
    }
};

int main() {
    CarpoolApp carpoolApp;

    int choice;
    do {
        std::cout << "====== Carpool App Menu ======" << std::endl;
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Sign Up" << std::endl;
        std::cout << "3. Carpool" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "Enter your choice (1-4): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                carpoolApp.login();
                break;
            case 2:
                carpoolApp.signUp();
                break;
            case 3:
                carpoolApp.carpool();
                break;
            case 4:
                std::cout << "Exiting the Carpool App. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 4." << std::endl;
        }

    } while (choice != 4);

    return 0;
}
