#ifndef MODEL_H
#define MODEL_H

#include <ctime>
#include <vector>
#include <type_traits>
#include <cmath>
#include <cstdlib>
#include <fstream>

#include <QDebug>

class Model
{
    clock_t start;
    float x, y, x_prev, y_prev;
    int canvasSize;
    float diameter;
    std::vector<float> times;
    std::vector<float> distances;

public:
    Model(int canvasSize);
    void startTimer()
    {
        start = clock();
        x_prev = x;
        y_prev = y;
        x = rand() % (canvasSize - static_cast<int>(diameter));
        y = rand() % (canvasSize - static_cast<int>(diameter));
    }
    void stopTimer()
    {
        auto ticks = clock() - start;
        times.push_back(static_cast<float>(ticks)/CLOCKS_PER_SEC);
        float d = sqrt(pow(x - x_prev, 2) + pow(y - y_prev, 2));
        distances.push_back(d);
    }
    const std::vector<float> &getTimes()
    {
        return times;
    }
    const std::vector<float> &getDistances()
    {
        return distances;
    }
    float getLastTime()
    {
        return times.size() ? times.back() : 0.f;
    }
    float getLastDistance()
    {
        return distances.size() ? distances.back() : 0.f;
    }
    void clearMeasures()
    {
        times.clear();
        distances.clear();
    }
    float getX()
    {
        return x;
    }
    float getY()
    {
        return y;
    }
    float getDiameter()
    {
        return diameter;
    }
    bool saveFile(const std::string &fileName)
    {
        std::ofstream f(fileName, std::ios::trunc);
        if(!f.is_open())
            return false;
        f << "times" << ',' << "distances" << '\n';
        for(int i = 0; i < times.size(); ++i)
        {
            f << times[i] << ',' << distances[i] << '\n';
        }
        f.close();
        return true;
    }
};

#endif // MODEL_H
