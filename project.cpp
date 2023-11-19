#include <iostream>
#include <vector>
#include <string>
//this is a changed file.
// changed file 2
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
    std::string id;
    std::string name;
    Profile profile;

    User(const std::string& userId, const std::string& userName, const Profile& userProfile)
        : id(userId), name(userName), profile(userProfile) {}
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

class CarpoolApp {
private:
    std::vector<User> users;
    User* currentUser;
    std::vector<CarpoolRequest> carpoolRequests;

public:
    CarpoolApp() : currentUser(nullptr) {}

    void signUp() {
        std::string userId, userName, userRole, userYear, userCourse, userBatch;
        std::cout << "Enter your user ID: ";
        std::cin >> userId;

        if (findUserById(userId) != nullptr) {
            std::cout << "User ID already exists. Please choose a different one." << std::endl;
            return;
        }

        std::cout << "Enter your name: ";
        std::cin >> userName;

        std::cout << "Are you a student or a professor? ";
        std::cin >> userRole;

        std::cout << "Enter your year: ";
        std::cin >> userYear;

        std::cout << "Enter your course: ";
        std::cin >> userCourse;

        if (userRole == "student") {
            std::cout << "Enter your batch: ";
            std::cin >> userBatch;
        } else {
            userBatch = "";  // Empty for professors
        }

        Profile userProfile(userRole, userYear, userCourse, userBatch);
        users.push_back(User(userId, userName, userProfile));

        std::cout << "Registration successful!" << std::endl;
    }

    void login() {
        std::string userId;
        std::cout << "Enter your user ID: ";
        std::cin >> userId;

        currentUser = findUserById(userId);

        if (currentUser != nullptr) {
            std::cout << "Login successful! User details:" << std::endl;
            std::cout << "ID: " << currentUser->id << ", Name: " << currentUser->name << ", Role: " << currentUser->profile.role
                      << ", Year: " << currentUser->profile.year << ", Course: " << currentUser->profile.course
                      << ", Batch: " << currentUser->profile.batch << std::endl;

            int option;
            do {
                std::cout << "====== Logged-In User Menu ======" << std::endl;
                std::cout << "1. Carpool" << std::endl;
                std::cout << "2. View Carpool History" << std::endl;
                std::cout << "3. Logout" << std::endl;
                std::cout << "==============================" << std::endl;
                std::cout << "Enter your option (1-3): ";
                std::cin >> option;

                switch (option) {
                    case 1:
                        carpool();
                        break;
                    case 2:
                        std::cout << "View Carpool History functionality placeholder. Implement as needed." << std::endl;
                        break;
                    case 3:
                        logout();
                        break;
                    default:
                        std::cout << "Invalid option. Please enter a number between 1 and 3." << std::endl;
                }

            } while (option != 3);
        } else {
            std::cout << "User not found. Please check your user ID and try again." << std::endl;
        }
    }

    void logout() {
        currentUser = nullptr;
        std::cout << "Logout successful. Goodbye!" << std::endl;
    }

    void carpool() {
        int option;
        do {
            std::cout << "====== Carpool Menu ======" << std::endl;
            std::cout << "1. Offer a Carpool" << std::endl;
            std::cout << "2. View Carpool Requests" << std::endl;
            std::cout << "3. Match Carpool Requests" << std::endl;
            std::cout << "4. Return to User Menu" << std::endl;
            std::cout << "===========================" << std::endl;
            std::cout << "Enter your option (1-4): ";
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
                    return;
                default:
                    std::cout << "Invalid option. Please enter a number between 1 and 4." << std::endl;
            }

        } while (option != 4);
    }

private:
    User* findUserById(const std::string& userId) {
        for (auto& user : users) {
            if (user.id == userId) {
                return &user;
            }
        }
        return nullptr;
    }

    void offerCarpool() {
        std::string loc, time, date;
        int type;

        std::cout << "Enter carpool details:" << std::endl;
        std::cout << "Location: ";
        std::cin >> loc;
        std::cout << "Date: ";
        std::cin >> date;
        std::cout << "Time: ";
        std::cin >> time;
        std::cout << "Vehicle Type (2 or 4 persons): ";
        std::cin >> type;

        carpoolRequests.push_back(CarpoolRequest(loc, time, date, type));

        std::cout << "Carpool request added successfully!" << std::endl;
    }

    void viewCarpoolRequests() {
        std::cout << "All carpool requests:" << std::endl;
        for (const auto& request : carpoolRequests) {
            std::cout << "Location: " << request.location << ", Date: " << request.date
                      << ", Time: " << request.time << ", Vehicle Type: " << request.vehicleType << std::endl;
        }
    }

    void matchCarpoolRequests() {
        if (carpoolRequests.size() < 2) {
            std::cout << "Not enough carpool requests to match." << std::endl;
            return;
        }

        // Assume currentUser's carpool request
        // Assume currentUser's carpool request is at index 0
        CarpoolRequest currentUserRequest = carpoolRequests[0];

        for (size_t i = 1; i < carpoolRequests.size(); ++i) {
            CarpoolRequest otherRequest = carpoolRequests[i];

            if (areRequestsCompatible(currentUserRequest, otherRequest)) {
                std::cout << "Compatible carpool found!" << std::endl;
                displayCarpoolMatch(currentUserRequest, otherRequest);
            }
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
