#include <iostream>
#include <conio.h> // For _getch()
#include <vector>
#include <fstream>
#include <string>
#include <iomanip> // For setw
#include <map>     // For std::map in LoyaltyProgram
#include <algorithm> // For std::remove, std::rename

using namespace std;

// Forward declarations for classes used as pointers/references
class SeatManager;
class PaymentGateway;
class NotificationService;
class LoyaltyProgram;
class AnalyticsDashboard;

// ===================== STRUCTS =====================
struct ticket
{
    string cnic;
    string movie_name;
    string day;
};

struct movieReview
{
    string cnic;
    string movie_name;
    string Review;
    int rating;
};

struct SimpleMovieStats {
    string movie_name;
    int total_rating_sum;
    int review_count;
    double average_rating; // To store the calculated average

    // Constructor to easily initialize when creating a new stat entry
    SimpleMovieStats(string name = "", int rating = 0) :
        movie_name(name), total_rating_sum(rating), review_count(1), average_rating(0.0) {}
};

// ===================== ABSTRACT BASE CLASS =====================
class motiveTheater
{
public:
    virtual void purposeofthisTheater() = 0;
};

// ===================== CORE MOVIE CLASS =====================
class movie
{
protected:
    const int total_tickets = 100;
    static int available_tickets;

public:
    void showAvailableTickets()
    {
        cout << total_tickets;
    }
    static int returnAvailableTickets()
    {
        return available_tickets;
    }
    void movieList()
    {
        cout << "1.Pathan" << endl;
        cout << "2.Shiddat" << endl;
        cout << "3.Azadi" << endl;
        cout << "4.Lifetime" << endl;
        cout << "5.Afghani" << endl;
        cout << "6.Sita Ramam" << endl;
        cout << "7.Mission Impossible 7" << endl;
        cout << "8.Kudo" << endl;
        cout << "9.Loyality matters" << endl;
        cout << "10.Power is power" << endl;
    }
};

// Initialize static member
int movie::available_tickets = 100;

// ===================== FILE HANDLING BASE CLASS =====================
class handlingFiles : public movie
{
public:
    void bookTicket_file(const ticket& T) // Pass ticket object directly
    {
        ofstream file;
        file.open("tickets.txt", ios::app);
        file << T.cnic << "\t" << T.movie_name << "\t" << T.day << endl;
        file.close();

        // 🎟 Show the ticket receipt here
        cout << "\n============= 🎟 Ticket Receipt =============\n";
        cout << "✔ Ticket successfully booked!\n";
        cout << "CNIC         : " << T.cnic << endl;
        cout << "Movie        : " << T.movie_name << endl;
        cout << "Day          : " << T.day << endl;
        cout << "=============================================\n";
    }

    void reviewFilm(string CNIC)
    {
        ifstream ifs;
        ofstream ofs;
        ticket T;
        movieReview R;
        ifs.open("tickets.txt");
        ofs.open("reviews.txt", ios::app);

        bool cnicFound = false;
        while (ifs >> T.cnic >> T.movie_name >> T.day) // Read all fields
        {
            if (CNIC == T.cnic)
            {
                cnicFound = true;
                cout << "CNIC FOUND" << endl;
                int n;
                cout << "Enter your review" << endl;
                cout << "Select the movie" << endl;
                movieList();
                cin >> n;

                // Assign movie name based on choice
                if (n == 1) R.movie_name = "Pathan";
                else if (n == 2) R.movie_name = "Shiddat";
                else if (n == 3) R.movie_name = "Azadi";
                else if (n == 4) R.movie_name = "LifeTime";
                else if (n == 5) R.movie_name = "Afghani";
                else if (n == 6) R.movie_name = "Sita Ramam";
                else if (n == 7) R.movie_name = "Mission Impossible 7";
                else if (n == 8) R.movie_name = "Kudo";
                else if (n == 9) R.movie_name = "Loyality matters";
                else if (n == 10) R.movie_name = "Power is power";
                else {
                    cout << "Invalid movie choice." << endl;
                    ifs.close();
                    ofs.close();
                    return;
                }

                R.cnic = CNIC;
                cout << "Enter your review in a liner (no spaces):" << endl; // Changed to single word input for simplicity with cin
                cin >> R.Review;
                cout << "Also enter the rating for the Film 1-5" << endl;
                cin >> R.rating;

                ofs << R.cnic << "\t" << R.movie_name << "\t" << R.Review << "\t" << R.rating << endl;
                cout << "Review submitted " << endl;
                cout << "Thanks for your feedback" << endl;
                ifs.close();
                ofs.close();
                return; // Exit after finding and processing CNIC
            }
        }

        ifs.close();
        ofs.close();

        if (!cnicFound) {
            cout << "You haven't bought a ticket." << endl;
            cout << "Only persons who buy a ticket can review." << endl;
        }
    }

    void showAllmoviesReviews()
    {
        movieReview r;
        ifstream ifs;
        ifs.open("reviews.txt");
        if (!ifs.is_open()) {
            cout << "No reviews available." << endl;
            return;
        }
        cout << "\n--- All Movie Reviews ---\n";
        while (ifs >> r.cnic >> r.movie_name >> r.Review >> r.rating)
        {
            cout << "CNIC: " << r.cnic
                 << " | Movie: " << r.movie_name
                 << " | Review: " << r.Review
                 << " | Rating: " << r.rating << endl;
        }
        ifs.close();
    }
};

// ===================== NEW UTILITY CLASSES (Composition) =====================
class SeatManager {
private:
    const int ROWS = 10;
    const int SEATS_PER_ROW = 15;
    vector<vector<bool>> seatMap;

public:
    SeatManager() {
        seatMap.resize(ROWS, vector<bool>(SEATS_PER_ROW, false)); // Initialize all seats as available
    }

    void displaySeatMap() {
        cout << "\n     SCREEN THIS WAY\n";
        cout << "   ";
        for (int i = 1; i <= SEATS_PER_ROW; i++) {
            cout << setw(3) << i;
        }
        cout << endl;

        for (int row = 0; row < ROWS; row++) {
            cout << char('A' + row) << " |";
            for (int seat = 0; seat < SEATS_PER_ROW; seat++) {
                cout << (seatMap[row][seat] ? " X " : " O ");
            }
            cout << endl;
        }
    }

    bool bookSeat(char rowChar, int seatNum) {
        int row = toupper(rowChar) - 'A';
        seatNum--; // Convert to 0-based index

        if (row < 0 || row >= ROWS || seatNum < 0 || seatNum >= SEATS_PER_ROW) {
            cout << "Invalid seat selection.\n";
            return false; // Invalid seat selection
        }

        if (!seatMap[row][seatNum]) {
            seatMap[row][seatNum] = true; // Mark seat as booked
            return true;
        }
        cout << "Seat " << rowChar << seatNum + 1 << " is already booked.\n";
        return false; // Seat already booked
    }
};

class PaymentGateway {
public:
    bool processPayment(double amount) {
        string cardNumber;
        cout << "Enter 16-digit card number: ";
        cin >> cardNumber;

        if (cardNumber.length() != 16) {
            cout << "Invalid card number! Payment failed.\n";
            return false;
        }

        cout << "Processing payment of Rs." << amount << "...\n";
        // Simulate payment processing
        cout << "Payment successful!\n";
        return true; // Assume payment is successful
    }
};

class AnalyticsDashboard {
public:
    void showRevenueReport() {
        ifstream file("tickets.txt");
        string line;
        int totalTickets = 0;

        if (!file.is_open()) {
            cout << "No ticket data available for revenue report.\n";
            return;
        }

        while (getline(file, line)) {
            totalTickets++;
        }
        file.close();

        cout << "\n--- Revenue Report ---\n";
        cout << "Total Tickets Sold: " << totalTickets << endl;
        cout << "Estimated Revenue (assuming Rs. 500/ticket): Rs." << totalTickets * 500 << endl;
    }

    void showTopMovies() {
        // This function is now implemented in FilmReviews::topmovies()
        // You can call that function here if you want to show it from Admin
        cout << "Top Movies based on ratings (see User Menu -> View Top Movies):\n";
    }
};

class NotificationService {
public:
    void sendBookingConfirmation(const ticket& t) {
        cout << "Sending booking confirmation for " << t.movie_name << " to " << t.cnic << endl;
    }

    void sendReviewAcknowledgment(const movieReview& r) {
        cout << "Thank you for your review on " << r.movie_name << "!" << endl;
    }
};

class LoyaltyProgram {
private:
    map<string, int> pointsMap; // CNIC -> Points

public:
    void addPoints(const string& cnic, int points) {
        pointsMap[cnic] += points;
        cout << "Added " << points << " loyalty points for CNIC: " << cnic << endl;
    }

    void redeemPoints(const string& cnic) {
        if (pointsMap.count(cnic) && pointsMap[cnic] >= 10) {
            pointsMap[cnic] -= 10; // Redeem 10 points
            cout << "Redeemed 10 points for CNIC: " << cnic << endl;
        } else {
            cout << "Not enough points to redeem for CNIC: " << cnic << endl;
        }
    }
};

// ===================== USER CLASS =====================
class User
{
private:
    string name;
    int age;
    string cnic; // Changed to string for consistency with ticket/review structs

public:
    void getUserData()
    {
        cout << "Enter your name: ";
        cin.ignore(); // Clear buffer before getline
        getline(cin, name);
        cout << "Enter your age: ";
        cin >> age;
        cout << "Enter your CNIC: ";
        cin >> cnic;

        // Save to file
        ofstream file("customers.txt", ios::app);
        if (!file.is_open()) {
            cout << "Error opening customers.txt for writing.\n";
            return;
        }
        file << name << "\t" << age << "\t" << cnic << endl;
        file.close();
    }

    void showUserData()
    {
        cout << "Name: " << name << endl;
        cout << "CNIC: " << cnic << endl;
        cout << "Age: " << age << endl;
    }

    string getCNIC() // Return string
    {
        return cnic;
    }
    string getName() {
        return name;
    }
};

// ===================== BOOK TICKETS CLASS =====================
class BookTickets : public handlingFiles
{
private:
    SeatManager* seatManager;
    PaymentGateway* paymentGateway;
    NotificationService* notifier;
    LoyaltyProgram* loyalty;

public:
    BookTickets(SeatManager* sm, PaymentGateway* pg, NotificationService* ns, LoyaltyProgram* lp)
        : seatManager(sm), paymentGateway(pg), notifier(ns), loyalty(lp) {}

    void bookTicket()
    {
        if (returnAvailableTickets() == 0)
        {
            cout << "Sorry, no tickets available at the moment." << endl;
            return;
        }

        User u;
        u.getUserData(); // Collect user info first

        int movieChoice;
        movieList(); // Display movie list
        cout << "Enter your movie choice: ";
        cin >> movieChoice;

        ticket T; // Declare ticket object here
        T.cnic = u.getCNIC();
        T.day = "Friday"; // Default day

        // Assign movie name based on choice
        if (movieChoice == 1) T.movie_name = "Pathan";
        else if (movieChoice == 2) T.movie_name = "Shiddat";
        else if (movieChoice == 3) T.movie_name = "Azadi";
        else if (movieChoice == 4) T.movie_name = "LifeTime";
        else if (movieChoice == 5) T.movie_name = "Afghani";
        else if (movieChoice == 6) T.movie_name = "Sita Ramam";
        else if (movieChoice == 7) T.movie_name = "Mission Impossible 7";
        else if (movieChoice == 8) T.movie_name = "Kudo";
        else if (movieChoice == 9) T.movie_name = "Loyality matters";
        else if (movieChoice == 10) T.movie_name = "Power is power";
        else {
            cout << "Invalid movie choice. Ticket booking cancelled." << endl;
            return;
        }

        seatManager->displaySeatMap();
        char rowChar;
        int seatNum;
        cout << "Enter desired seat (e.g., A5): ";
        cin >> rowChar >> seatNum;

        if (seatManager->bookSeat(rowChar, seatNum)) {
            if (paymentGateway->processPayment(500.0)) { // Assuming ticket price is 500
                bookTicket_file(T); // Write ticket to file
                notifier->sendBookingConfirmation(T); // Send confirmation
                loyalty->addPoints(T.cnic, 10); // Add loyalty points
                movie::available_tickets--; // Decrease available tickets
            } else {
                cout << "Payment failed. Ticket not booked.\n";
            }
        } else {
            cout << "Seat booking failed. Ticket not booked.\n";
        }
    }
};

// ===================== FILM REVIEWS CLASS =====================
class FilmReviews : public handlingFiles
{
public:
    void addmovieReview()
    {
        string Cnic;
        cout << "Enter your CNIC to add a review: ";
        cin >> Cnic;
        reviewFilm(Cnic);
    }
    void ShowFilmReviws()
    {
        cout << "Film reviews" << endl;
        showAllmoviesReviews();
    }
    void topmovies()
    {
        ifstream ifs("reviews.txt");
        if (!ifs.is_open()) {
            cout << "No reviews available to determine top movies." << endl;
            return;
        }

        vector<SimpleMovieStats> movieStatsList; // To store aggregated data for each unique movie
        movieReview r;

        // 1. Read all reviews and aggregate data
        while (ifs >> r.cnic >> r.movie_name >> r.Review >> r.rating) {
            bool foundMovie = false;
            // Check if this movie already exists in our list
            for (size_t i = 0; i < movieStatsList.size(); ++i) {
                if (movieStatsList[i].movie_name == r.movie_name) {
                    movieStatsList[i].total_rating_sum += r.rating;
                    movieStatsList[i].review_count++;
                    foundMovie = true;
                    break;
                }
            }
            // If movie not found, add it as a new entry
            if (!foundMovie) {
                SimpleMovieStats newStats(r.movie_name, r.rating); // Use constructor
                movieStatsList.push_back(newStats);
            }
        }
        ifs.close(); // Close the reviews file

        if (movieStatsList.empty()) {
            cout << "No movies found with ratings." << endl;
            return;
        }

        // 2. Calculate average rating for each movie
        for (size_t i = 0; i < movieStatsList.size(); ++i) {
            if (movieStatsList[i].review_count > 0) {
                movieStatsList[i].average_rating = static_cast<double>(movieStatsList[i].total_rating_sum) / movieStatsList[i].review_count;
            } else {
                movieStatsList[i].average_rating = 0.0; // Should not happen if count > 0
            }
        }

        // 3. Manually sort the movies by average rating in descending order (using Bubble Sort)
        for (size_t i = 0; i < movieStatsList.size() - 1; ++i) {
            for (size_t j = 0; j < movieStatsList.size() - 1 - i; ++j) {
                if (movieStatsList[j].average_rating < movieStatsList[j+1].average_rating) {
                    // Swap elements if the current one is smaller than the next
                    SimpleMovieStats temp = movieStatsList[j];
                    movieStatsList[j] = movieStatsList[j+1];
                    movieStatsList[j+1] = temp;
                }
            }
        }

        cout << "\n--- Movies by Average Rating  ---\n";
        for (size_t i = 0; i < movieStatsList.size(); ++i) {
            cout << i + 1 << ". " << movieStatsList[i].movie_name
            << " (Average Rating: " << fixed << setprecision(2) << movieStatsList[i].average_rating << "/5.0)" << endl;
        }
    }
};

// ===================== TICKET MANAGEMENT CLASSES =====================
class SearchTicket : public handlingFiles
{
public:
    void findTicketByCNIC()
    {
        string searchCnic;
        cout << "Enter CNIC to search ticket: ";
        cin >> searchCnic;

        ifstream file("tickets.txt");
        if (!file.is_open()) {
            cout << "No tickets found.\n";
            return;
        }
        ticket T;
        bool found = false;

        while (file >> T.cnic >> T.movie_name >> T.day)
        {
            if (T.cnic == searchCnic)
            {
                found = true;
                cout << "Ticket Found:" << endl;
                cout << "CNIC: " << T.cnic << endl;
                cout << "Movie: " << T.movie_name << endl;
                cout << "Day: " << T.day << endl;
                break;
            }
        }

        if (!found)
        {
            cout << "No ticket found with this CNIC." << endl;
        }
        file.close();
    }
};

class CancelTicket : public handlingFiles
{
public:
    void cancelTicketByCNIC()
    {
        string searchCnic;
        cout << "Enter CNIC to cancel ticket: ";
        cin >> searchCnic;

        ifstream inFile("tickets.txt");
        if (!inFile.is_open()) {
            cout << "No tickets to cancel.\n";
            return;
        }
        ofstream tempFile("temp.txt");
        if (!tempFile.is_open()) {
            cout << "Error creating temporary file.\n";
            inFile.close();
            return;
        }

        ticket T;
        bool found = false;

        while (inFile >> T.cnic >> T.movie_name >> T.day)
        {
            if (T.cnic == searchCnic)
            {
                found = true;
                cout << "Ticket cancelled for CNIC: " << T.cnic << endl;
                continue; // skip writing this record to temp file
            }
            tempFile << T.cnic << "\t" << T.movie_name << "\t" << T.day << endl;
        }

        inFile.close();
        tempFile.close();

        remove("tickets.txt");
        rename("temp.txt", "tickets.txt");

        if (!found)
        {
            cout << "No ticket found for given CNIC." << endl;
        }
    }
};

class ShowAllTickets : public handlingFiles
{
public:
    void displayAllTickets()
    {
        ifstream file("tickets.txt");
        if (!file.is_open()) {
            cout << "No tickets booked yet.\n";
            return;
        }
        ticket T;

        cout << "\n--- All Booked Tickets ---\n";
        cout << "--------------------------\n";
        while (file >> T.cnic >> T.movie_name >> T.day)
        {
            cout << "CNIC: " << T.cnic
                 << " | Movie: " << T.movie_name
                 << " | Day: " << T.day << endl;
        }
        file.close();
    }
};

// ===================== ADMIN CLASS =====================
class Admin : public movie, public motiveTheater
{
private:
    string adminPassword = "admin123"; // Admin login password
    AnalyticsDashboard* dashboard; // Changed to pointer

public:
    // Constructor to initialize dashboard
    Admin(AnalyticsDashboard* ad) : dashboard(ad) {}

    bool authenticate()
    {
        char ch;
        string input;
        cout << "Enter admin password: ";
        while ((ch = _getch()) != 13) { // 13 is ASCII for Enter key
            if (ch == 8) { // 8 is ASCII for Backspace
                if (!input.empty()) {
                    input.erase(input.size() - 1);
                    cout << "\b \b"; // Erase character from console
                }
            } else {
                input += ch;
                cout << '*'; // Print asterisk for password character
            }
        }
        cout << endl; // New line after password input

        if (input == adminPassword)
            return true;
        cout << "\nWrong password. Access denied.\n";
        return false;
    }

    void showReports() {
        if (!authenticate()) return;
        dashboard->showRevenueReport();
        // dashboard->showTopMovies(); // This calls the placeholder in AnalyticsDashboard
                                   // You might want to call FilmReviews::topmovies() here
    }

    void viewCustomerData()
    {
        if (!authenticate()) return;

        ifstream file("customers.txt");
        if (!file.is_open())
        {
            cout << "No customer data available.\n";
            return;
        }

        string name;
        int age;
        string cnic; // Changed to string
        cout << "\n--- Registered Customers ---\n";
        while (file >> name >> age >> cnic)
        {
            cout << "Name: " << name << " | Age: " << age << " | CNIC: " << cnic << endl;
        }
        file.close();
    }

    void addMovie() {
        if (!authenticate()) return;

        string newMovie;
        cout << "Enter new movie name to add: ";
        cin.ignore(); // Clear buffer
        getline(cin, newMovie);

        ofstream out("movies.txt", ios::app);
        if (!out) {
            cout << "❌ Failed to open movies.txt\n";
            return;
        }

        out << newMovie << endl;
        out.close();

        cout << "✅ Movie '" << newMovie << "' added successfully.\n";
    }

    void removeMovie() {
        if (!authenticate()) return;

        string movieToRemove;
        cout << "Enter movie name to remove: ";
        cin.ignore(); // Clear buffer
        getline(cin, movieToRemove);

        ifstream in("movies.txt");
        ofstream temp("temp.txt");

        if (!in || !temp) {
            cout << "❌ File error.\n";
            return;
        }

        string movie;
        bool found = false;

        while (getline(in, movie)) {
            if (movie != movieToRemove) {
                temp << movie << endl;
            } else {
                found = true;
            }
        }

        in.close();
        temp.close();

        remove("movies.txt");
        rename("temp.txt", "movies.txt");

        if (found) {
            cout << "✅ Movie '" << movieToRemove << "' removed.\n";
        } else {
            cout << "❌ Movie not found.\n";
        }
    }

    void showDynamicMovieList() {
        ifstream file("movies.txt");
        if (!file.is_open()) {
            cout << "No dynamic movie list available. Please add movies.\n";
            return;
        }
        string movie;
        int index = 1;

        cout << "\n--- Current Movie List ---\n";
        while (getline(file, movie)) {
            cout << index++ << ". " << movie << endl;
        }
        file.close();
    }

    void manageMoviesMenu() {
        if (!authenticate()) return;

        int choice;
        cout << "\n--- Admin Movie Management ---\n";
        cout << "1. Add Movie\n";
        cout << "2. Remove Movie\n";
        cout << "3. View Movie List\n";
        cout << "Enter choice: ";
        cin >> choice;
        // cin.ignore(); // No need to clear buffer here if next input is int

        if (choice == 1) {
            addMovie(); // Call the separate function
        } else if (choice == 2) {
            removeMovie(); // Call the separate function
        } else if (choice == 3) {
            showDynamicMovieList();
        } else {
            cout << "❌ Invalid choice.\n";
        }
    }

    void purposeofthisTheater() override // Mark as override
    {
        cout << "  ---------------PURPOSE OF THE THEATER--------------" << endl;
        cout << "  More than just movies, we're a heart of the community." << endl;
        cout << "  Bringing diverse stories, family fun, and cultural nights" << endl;
        cout << "  right to your neighborhood. We believe in cinema's power" << endl;
        cout << "  to connect, inspire, and entertain. Enjoy state-of-the-art" << endl;
        cout << "  sound, comfortable seating, and a welcoming atmosphere." << endl;
        cout << "  Every ticket supports local initiatives and vibrant arts." << endl;
        cout << "  Join us for unforgettable cinematic experiences and be" << endl;
        cout << "  part of something special. Your community, your cinema!" << endl;
    }
};

// ===================== INITIALIZATION FUNCTION =====================
void initializeMovieFileIfNeeded() {
    ifstream check("movies.txt");
    if (!check.is_open() || check.peek() == ifstream::traits_type::eof()) {
        check.close();
        ofstream out("movies.txt");
        if (out.is_open()) {
            out << "Pathan\nShiddat\nAzadi\nLifetime\nAfghani\n";
            out << "Sita Ramam\nMission Impossible 7\nKudo\nLoyality matters\nPower is power\n";
            out.close();
            cout << "✅ Initialized movie list in movies.txt\n";
        } else {
            cout << "❌ Could not create movies.txt\n";
        }
    } else {
        check.close();
    }
}

// ===================== MAIN FUNCTION =====================
int main() {
    // Initialize all services
    SeatManager seatManager;
    PaymentGateway paymentGateway;
    NotificationService notifier;
    LoyaltyProgram loyaltyProgram;
    AnalyticsDashboard analytics;
    motiveTheater* theater; // Pointer to base class for polymorphism

    // Initialize Admin with analytics dashboard
    Admin admin(&analytics);
    
    initializeMovieFileIfNeeded(); // Ensure movie list file exists

    int main_choice;
    bool running = true;

    while (running) {
        system("cls"); // Clears the console screen (Windows specific)
        cout << "=== MOVIE THEATER MANAGEMENT SYSTEM ===" << endl;
        cout << "1. User Menu" << endl;
        cout << "2. Admin Menu" << endl;
        cout << "3. About Our Theater" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> main_choice;

        switch (main_choice) {
            case 1: {  // User Menu
                FilmReviews fm;
                BookTickets booker(&seatManager, &paymentGateway, &notifier, &loyaltyProgram);
                ShowAllTickets st;
                CancelTicket cct;
                SearchTicket tt;
                
                int user_choice;
                bool in_user_menu = true;
                
                while (in_user_menu) {
                    system("cls");
                    cout << "=== USER MENU ===" << endl;
                    cout << "1. View Movie List" << endl;
                    cout << "2. Book Ticket" << endl;
                    cout << "3. Add Review" << endl;
                    cout << "4. View All Reviews" << endl;
                    cout << "5. View Top Movies" << endl;
                    cout << "6. Search Ticket" << endl;
                    cout << "7. Cancel Ticket" << endl;
                    cout << "8. View All Tickets" << endl;
                    cout << "9. About Our Theater" << endl;
                    cout << "0. Back to Main Menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> user_choice;

                    switch (user_choice) {
                        case 1:
                            admin.showDynamicMovieList();
                            break;
                        case 2:
                            booker.bookTicket(); // Corrected variable name
                            break;
                        case 3:
                            fm.addmovieReview();
                            break;
                        case 4:
                            fm.ShowFilmReviws();
                            break;
                        case 5:
                            fm.topmovies();
                            break;
                        case 6:
                            tt.findTicketByCNIC();
                            break;
                        case 7:
                            cct.cancelTicketByCNIC();
                            break;
                        case 8:
                            st.displayAllTickets();
                            break;
                        case 9:
                            theater = &admin; // Assign admin object to base pointer
                            theater->purposeofthisTheater();
                            break;
                        case 0:
                            in_user_menu = false;
                            continue;
                        default:
                            cout << "Invalid choice!" << endl;
                    }
                    cout << "\nPress Enter to continue...";
                    cin.ignore(); // Consume newline character left by cin >> user_choice
                    cin.get();    // Wait for user to press Enter
                }
                break;
            }
            case 2: {  // Admin Menu
                int admin_choice;
                bool in_admin_menu = true;
                
                while (in_admin_menu) {
                    system("cls");
                    cout << "=== ADMIN MENU ===" << endl;
                    cout << "1. Show Reports" << endl;
                    cout << "2. Manage Movies" << endl;
                    cout << "3. View Customer Data" << endl;
                    cout << "4. About Our Theater" << endl;
                    cout << "0. Back to Main Menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> admin_choice;

                    switch (admin_choice) {
                        case 1:
                            admin.showReports();
                            break;
                        case 2:
                            admin.manageMoviesMenu();
                            break;
                        case 3:
                            admin.viewCustomerData();
                            break;
                        case 4:
                            theater = &admin; // Assign admin object to base pointer
                            theater->purposeofthisTheater();
                            break;
                        case 0:
                            in_admin_menu = false;
                            continue;
                        default:
                            cout << "Invalid choice!" << endl;
                    }
                    cout << "\nPress Enter to continue...";
                    cin.ignore(); // Consume newline character left by cin >> admin_choice
                    cin.get();    // Wait for user to press Enter
                }
                break;
            }
            case 3: {  // About Theater
                theater = &admin; // Assign admin object to base pointer
                theater->purposeofthisTheater();
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            }
            case 0:
                running = false;
                break;
            default:
                cout << "Invalid choice!" << endl;
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
        }
    }

    return 0;
}
