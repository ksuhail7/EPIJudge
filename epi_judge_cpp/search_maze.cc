#include <istream>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

using std::vector;
enum class Color {
    kWhite, kBlack
};

struct Coordinate {
    bool operator==(const Coordinate &that) const {
        return x == that.x && y == that.y;
    }

    int x, y;
};

// followup questions:
// 1. how big is the maze?
// 2. is it guaranteed to have a unique path?
// 3. White is open and Black is blocked
// 4. can we move diagonal?
// 5. does return vector including start and end co-ordinates

bool SolveMaze(vector<vector<Color>> maze, const Coordinate &s, const Coordinate &e, vector<Coordinate> &path, int rows, int cols, vector<vector<bool>>& visited) {
    if(s == e) {
        path.push_back(s);
        return true;
    }

    if(visited[s.x][s.y])
        return false;
    visited[s.x][s.y] = true;
    bool hasPath = false;
    // move up
    int up_x = s.x - 1, up_y = s.y;
    if(!hasPath && up_x >= 0 && up_x < rows && maze[up_x][up_y] != Color::kBlack) {
        hasPath = SolveMaze(maze, {.x =  up_x, .y= up_y}, e, path, rows, cols, visited);

    }

    // move down
    int down_x = s.x + 1, down_y = s.y;
    if(!hasPath && down_x >= 0 && down_x < rows && maze[down_x][down_y] != Color::kBlack) {
        hasPath = SolveMaze(maze, {.x =  down_x, .y= down_y}, e, path, rows, cols, visited);
    }

    // move left;
    int left_x = s.x, left_y = s.y - 1;

    if(!hasPath && left_y >=0 && left_y < cols && maze[left_x][left_y] != Color::kBlack) {
        hasPath = SolveMaze(maze, {.x =  left_x, .y= left_y}, e, path, rows, cols, visited);
    }

    int right_x = s.x, right_y = s.y + 1;
    if(!hasPath && right_y >= 0 && right_y < cols && maze[right_x][right_y] != Color::kBlack) {
        hasPath = SolveMaze(maze, {.x=right_x, .y=right_y}, e, path, rows, cols, visited);
    }
    visited[s.x][s.y] = false;
    if(hasPath) {
        path.push_back(s);
        return true;
    }
    return false;

}

vector<Coordinate> SearchMaze(vector<vector<Color>> maze, const Coordinate &s,
                              const Coordinate &e) {
    // TODO - you fill in here.
    vector<Coordinate> path;
    int rows = maze.size();
    int cols = rows > 0 ? maze[0].size() : 0;
    if(rows < 1 || cols < 1) return {};
    vector<vector<bool>> visited(rows);
    for(int i = 0; i < rows; ++i) {
        visited[i].assign(cols, false);
    }
    if(SolveMaze(maze, s, e, path, rows, cols, visited)) {
        std::reverse(path.begin(), path.end());
        return path;
    } else {
        return {};
    }
}

namespace test_framework {
    template<>
    struct SerializationTrait<Color> : SerializationTrait<int> {
        using serialization_type = Color;

        static serialization_type Parse(const json &json_object) {
            return static_cast<serialization_type>(
                    SerializationTrait<int>::Parse(json_object));
        }
    };
}  // namespace test_framework

namespace test_framework {
    template<>
    struct SerializationTrait<Coordinate> : UserSerTrait<Coordinate, int, int> {
        static std::vector<std::string> GetMetricNames(const std::string &arg_name) {
            return {};
        }

        static std::vector<int> GetMetrics(const Coordinate &x) { return {}; }
    };
}  // namespace test_framework

bool PathElementIsFeasible(const vector<vector<Color>> &maze,
                           const Coordinate &prev, const Coordinate &cur) {
    if (!(0 <= cur.x && cur.x < maze.size() && 0 <= cur.y &&
          cur.y < maze[cur.x].size() && maze[cur.x][cur.y] == Color::kWhite)) {
        return false;
    }
    return cur == Coordinate{prev.x + 1, prev.y} ||
           cur == Coordinate{prev.x - 1, prev.y} ||
           cur == Coordinate{prev.x, prev.y + 1} ||
           cur == Coordinate{prev.x, prev.y - 1};
}

bool SearchMazeWrapper(TimedExecutor &executor,
                       const vector<vector<Color>> &maze, const Coordinate &s,
                       const Coordinate &e) {
    vector<vector<Color>> copy = maze;

    auto path = executor.Run([&] { return SearchMaze(copy, s, e); });

    if (path.empty()) {
        return s == e;
    }

    if (!(path.front() == s) || !(path.back() == e)) {
        throw TestFailure("Path doesn't lay between start and end points");
    }

    for (size_t i = 1; i < path.size(); i++) {
        if (!PathElementIsFeasible(maze, path[i - 1], path[i])) {
            throw TestFailure("Path contains invalid segments");
        }
    }

    return true;
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"executor", "maze", "s", "e"};
    return GenericTestMain(args, "search_maze.cc", "search_maze.tsv",
                           &SearchMazeWrapper, DefaultComparator{}, param_names);
}
