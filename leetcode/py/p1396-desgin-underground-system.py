# LeetCode 1396. Design underground system.

import math


class UndergroundSystem:
    def __init__(self):
        # id -> (start_station_name, start_time)
        self.current_rides = {}

        # (start_station_name, end_station_name) -> (total_time, num_rides)
        self.route_times = {}

    def checkIn(self, id: int, stationName: str, t: int) -> None:
        self.current_rides[id] = (stationName, t)

    def checkOut(self, id: int, stationName: str, t: int) -> None:
        start_station_name, t1 = self.current_rides.pop(id)
        key = (start_station_name, stationName)
        trip_time = float(t - t1)
        trips_info = self.route_times.get(key)
        if trips_info:
            trips_info[0] += trip_time
            trips_info[1] += 1
        else:
            self.route_times[key] = [trip_time, 1]

    def getAverageTime(self, startStation: str, endStation: str) -> float:
        key = (startStation, endStation)
        trips_info = self.route_times.get(key)
        if trips_info:
            return trips_info[0] / trips_info[1]
        return 0.0


if __name__ == "__main__":
    tests = (
        (
            ("in", 45, "Leyton", 3),
            ("in", 32, "Paradise", 8),
            ("in", 27, "Leyton", 10),
            ("out", 45, "Waterloo", 15),
            ("out", 27, "Waterloo", 20),
            ("out", 32, "Cambridge", 22),
            ("get", "Paradise", "Cambridge", 14.0),
            ("get", "Leyton", "Waterloo", 11.0),
            ("in", 10, "Leyton", 24),
            ("get", "Leyton", "Waterloo", 11.0),
            ("out", 10, "Waterloo", 38),
            ("get", "Leyton", "Waterloo", 12.0),
        ),
        (
            ("in", 10, "Leyton", 3),
            ("out", 10, "Paradise", 8),
            ("get", "Leyton", "Paradise", 5.0),
            ("in", 5, "Leyton", 10),
            ("out", 5, "Paradise", 16),
            ("get", "Leyton", "Paradise", 5.5),
            ("in", 2, "Leyton", 21),
            ("out", 2, "Paradise", 30),
            ("get", "Leyton", "Paradise", 6.666667),
        ),
    )
    for test in tests:
        underground_system = UndergroundSystem()
        for cmd, id, station_name, t in test:
            if cmd == "in":
                underground_system.checkIn(id, station_name, t)
            elif cmd == "out":
                underground_system.checkOut(id, station_name, t)
            elif cmd == "get":
                start_station_name = id
                exp = t
                act = underground_system.getAverageTime(
                    start_station_name, station_name
                )
                if not math.isclose(exp, act, rel_tol=1e-5, abs_tol=1e-5):
                    print(
                        f"Fail. {start_station_name} -> {station_name}: exp: {exp}, act: {act}"
                    )
