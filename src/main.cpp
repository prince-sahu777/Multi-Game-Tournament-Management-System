#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>

using namespace std;

const vector<string> GAMES = {
    "BGMI",
    "Free Fire",
    "Valorant",
    "Counter-Strike 2"
};

int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readLine(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

string chooseGame() {
    cout << "\nSelect game:\n";
    for (size_t i = 0; i < GAMES.size(); ++i) {
        cout << i + 1 << ". " << GAMES[i] << '\n';
    }
    int choice = readInt("Enter choice: ");
    if (choice < 1 || choice > static_cast<int>(GAMES.size())) {
        cout << "Invalid game selection.\n";
        return "";
    }
    return GAMES[choice - 1];
}

struct Player {
    int id;
    string name;
    string game;

    Player(int playerId, const string& playerName, const string& gameName)
        : id(playerId), name(playerName), game(gameName) {}

    void display() const {
        cout << "Player ID: " << id << " | Name: " << name
             << " | Game: " << game << '\n';
    }
};

struct Team {
    int id;
    string name;
    string game;

    Team(int teamId, const string& teamName, const string& gameName)
        : id(teamId), name(teamName), game(gameName) {}

    void display() const {
        cout << "Team ID: " << id << " | Team: " << name
             << " | Game: " << game << '\n';
    }
};

struct Tournament {
    int id;
    string name;
    string game;
    vector<int> teamIds;
    map<int, int> teamScores; // tournament-specific score for each team

    Tournament(int tournamentId, const string& tournamentName, const string& gameName)
        : id(tournamentId), name(tournamentName), game(gameName) {}

    void display() const {
        cout << "Tournament ID: " << id << " | Name: " << name
             << " | Game: " << game
             << " | Registered teams: " << teamIds.size() << '\n';
    }
};

class TournamentManager {
private:
    vector<Player> players;
    vector<Team> teams;
    vector<Tournament> tournaments;

    Player* findPlayer(int id) {
        for (auto& player : players)
            if (player.id == id) return &player;
        return nullptr;
    }

    Team* findTeam(int id) {
        for (auto& team : teams)
            if (team.id == id) return &team;
        return nullptr;
    }

    Tournament* findTournament(int id) {
        for (auto& tournament : tournaments)
            if (tournament.id == id) return &tournament;
        return nullptr;
    }

    const Tournament* findTournament(int id) const {
        for (const auto& tournament : tournaments)
            if (tournament.id == id) return &tournament;
        return nullptr;
    }

    bool teamRegistered(const Tournament& tournament, int teamId) const {
        return find(tournament.teamIds.begin(), tournament.teamIds.end(), teamId)
               != tournament.teamIds.end();
    }

public:
    void registerPlayer() {
        int id = readInt("Enter player ID (positive number): ");
        if (id <= 0 || findPlayer(id)) {
            cout << "Invalid or already-used player ID.\n";
            return;
        }

        string name = readLine("Enter player name: ");
        if (name.empty()) {
            cout << "Name cannot be empty.\n";
            return;
        }

        string game = chooseGame();
        if (game.empty()) return;

        players.emplace_back(id, name, game);
        cout << "Player registered successfully.\n";
    }

    void showPlayers() const {
        if (players.empty()) {
            cout << "No players registered yet.\n";
            return;
        }
        cout << "\n--- REGISTERED PLAYERS ---\n";
        for (const auto& player : players) player.display();
    }

    void searchPlayer() const {
        int id = readInt("Enter player ID to search: ");
        for (const auto& player : players) {
            if (player.id == id) {
                player.display();
                return;
            }
        }
        cout << "Player not found.\n";
    }

    void createTeam() {
        int id = readInt("Enter team ID (positive number): ");
        for (const auto& team : teams) {
            if (team.id == id) {
                cout << "Team ID already exists.\n";
                return;
            }
        }
        if (id <= 0) {
            cout << "Team ID must be positive.\n";
            return;
        }

        string name = readLine("Enter team name: ");
        if (name.empty()) {
            cout << "Team name cannot be empty.\n";
            return;
        }

        string game = chooseGame();
        if (game.empty()) return;

        teams.emplace_back(id, name, game);
        cout << "Team created successfully.\n";
    }

    void showTeams() const {
        if (teams.empty()) {
            cout << "No teams created yet.\n";
            return;
        }
        cout << "\n--- TEAMS ---\n";
        for (const auto& team : teams) team.display();
    }

    void createTournament() {
        int id = readInt("Enter tournament ID (positive number): ");
        if (id <= 0 || findTournament(id)) {
            cout << "Invalid or already-used tournament ID.\n";
            return;
        }

        string name = readLine("Enter tournament name: ");
        if (name.empty()) {
            cout << "Tournament name cannot be empty.\n";
            return;
        }

        string game = chooseGame();
        if (game.empty()) return;

        tournaments.emplace_back(id, name, game);
        cout << "Tournament created successfully.\n";
    }

    void showTournaments() const {
        if (tournaments.empty()) {
            cout << "No tournaments created yet.\n";
            return;
        }
        cout << "\n--- TOURNAMENTS ---\n";
        for (const auto& tournament : tournaments) tournament.display();
    }

    void registerTeamForTournament() {
        int tournamentId = readInt("Enter tournament ID: ");
        Tournament* tournament = findTournament(tournamentId);
        if (!tournament) {
            cout << "Tournament not found.\n";
            return;
        }

        int teamId = readInt("Enter team ID: ");
        Team* team = findTeam(teamId);
        if (!team) {
            cout << "Team not found.\n";
            return;
        }
        if (team->game != tournament->game) {
            cout << "The team's game does not match this tournament.\n";
            return;
        }
        if (teamRegistered(*tournament, teamId)) {
            cout << "This team is already registered in the tournament.\n";
            return;
        }

        tournament->teamIds.push_back(teamId);
        tournament->teamScores[teamId] = 0;
        cout << "Team registered for tournament successfully.\n";
    }

    void enterScore() {
        int tournamentId = readInt("Enter tournament ID: ");
        Tournament* tournament = findTournament(tournamentId);
        if (!tournament) {
            cout << "Tournament not found.\n";
            return;
        }

        int teamId = readInt("Enter registered team ID: ");
        if (!teamRegistered(*tournament, teamId)) {
            cout << "That team is not registered in this tournament.\n";
            return;
        }

        int score = readInt("Enter points earned in this match (0 or more): ");
        if (score < 0) {
            cout << "Score cannot be negative.\n";
            return;
        }

        tournament->teamScores[teamId] += score;
        cout << "Score added. Tournament total: "
             << tournament->teamScores[teamId] << '\n';
    }

    vector<pair<int, int>> getRankings(const Tournament& tournament) const {
        vector<pair<int, int>> rankings;
        for (int teamId : tournament.teamIds) {
            auto it = tournament.teamScores.find(teamId);
            int score = (it == tournament.teamScores.end()) ? 0 : it->second;
            rankings.push_back({teamId, score});
        }
        sort(rankings.begin(), rankings.end(),
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 if (a.second != b.second) return a.second > b.second;
                 return a.first < b.first;
             });
        return rankings;
    }

    void showRankings() const {
        int tournamentId = readInt("Enter tournament ID: ");
        const Tournament* tournament = findTournament(tournamentId);
        if (!tournament) {
            cout << "Tournament not found.\n";
            return;
        }

        auto rankings = getRankings(*tournament);
        cout << "\n=== RANKINGS: " << tournament->name
             << " (" << tournament->game << ") ===\n";

        if (rankings.empty()) {
            cout << "No teams registered in this tournament.\n";
            return;
        }

        int rank = 1;
        for (const auto& entry : rankings) {
            const Team* team = nullptr;
            for (const auto& item : teams)
                if (item.id == entry.first) team = &item;

            if (team) {
                cout << rank++ << ". " << team->name
                     << " | Team ID: " << team->id
                     << " | Points: " << entry.second << '\n';
            }
        }
    }

    void declareWinner() const {
        int tournamentId = readInt("Enter tournament ID: ");
        const Tournament* tournament = findTournament(tournamentId);
        if (!tournament) {
            cout << "Tournament not found.\n";
            return;
        }

        auto rankings = getRankings(*tournament);
        if (rankings.empty()) {
            cout << "Register at least one team first.\n";
            return;
        }

        int highestScore = rankings.front().second;
        cout << "\n=== WINNER: " << tournament->name << " ===\n";
        for (const auto& entry : rankings) {
            if (entry.second != highestScore) break;
            for (const auto& team : teams) {
                if (team.id == entry.first) {
                    cout << team.name << " with " << entry.second << " points!\n";
                    break;
                }
            }
        }
    }

    void saveRecords() const {
        ofstream playerFile("data/players.txt");
        ofstream teamFile("data/teams.txt");
        ofstream tournamentFile("data/tournaments.txt");
        ofstream registrationFile("data/registrations.txt");
        ofstream scoreFile("data/scores.txt");

        if (!playerFile || !teamFile || !tournamentFile ||
            !registrationFile || !scoreFile) {
            cout << "Could not open data files. Run the program from the project root folder.\n";
            return;
        }

        for (const auto& p : players)
            playerFile << p.id << '|' << p.name << '|' << p.game << '\n';

        for (const auto& t : teams)
            teamFile << t.id << '|' << t.name << '|' << t.game << '\n';

        for (const auto& t : tournaments)
            tournamentFile << t.id << '|' << t.name << '|' << t.game << '\n';

        for (const auto& tournament : tournaments) {
            for (int teamId : tournament.teamIds)
                registrationFile << tournament.id << '|' << teamId << '\n';

            for (const auto& score : tournament.teamScores)
                scoreFile << tournament.id << '|' << score.first
                          << '|' << score.second << '\n';
        }

        cout << "Records saved in the data/ folder.\n";
        cout << "Note: this version saves records but does not load them automatically on startup.\n";
    }

    void run() {
        int choice;
        do {
            cout << "\n============================================\n";
            cout << "   MULTI-GAME TOURNAMENT MANAGEMENT SYSTEM\n";
            cout << "============================================\n";
            cout << "1. Register player\n";
            cout << "2. Display players\n";
            cout << "3. Search player\n";
            cout << "4. Create team\n";
            cout << "5. Display teams\n";
            cout << "6. Create tournament\n";
            cout << "7. Display tournaments\n";
            cout << "8. Register team for tournament\n";
            cout << "9. Enter match score\n";
            cout << "10. Display tournament rankings\n";
            cout << "11. Declare winner\n";
            cout << "12. Save records\n";
            cout << "0. Exit\n";

            choice = readInt("Enter your choice: ");
            switch (choice) {
                case 1: registerPlayer(); break;
                case 2: showPlayers(); break;
                case 3: searchPlayer(); break;
                case 4: createTeam(); break;
                case 5: showTeams(); break;
                case 6: createTournament(); break;
                case 7: showTournaments(); break;
                case 8: registerTeamForTournament(); break;
                case 9: enterScore(); break;
                case 10: showRankings(); break;
                case 11: declareWinner(); break;
                case 12: saveRecords(); break;
                case 0: cout << "Thank you for using the system!\n"; break;
                default: cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 0);
    }
};

int main() {
    TournamentManager manager;
    manager.run();
    return 0;
}
