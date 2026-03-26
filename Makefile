CXX      = g++
CXXFLAGS = -Wall -std=c++11 -I. -I./Bestioles -I./CapteursEtAccessoires -I./Comportements -I./Creation -I./Observation  -I./Simulation -I./Visitor -I./Lib

SRCS = main.cpp \
       Bestioles/Bestiole.cpp \
	   CapteursEtAccessoires/DecCamouflage.cpp \
	   CapteursEtAccessoires/DecCarapace.cpp \
	   CapteursEtAccessoires/DecYeux.cpp \
	   CapteursEtAccessoires/DecOreilles.cpp \
	   CapteursEtAccessoires/DecNageoires.cpp \
       Simulation/Milieu.cpp \
       Simulation/Aquarium.cpp \
	   Comportements/Gregaire.cpp \
	   Comportements/Peureuse.cpp \
	   Comportements/Kamikaze.cpp \
	   Comportements/Prevoyante.cpp \
	   Comportements/PersonnalitesMultiples.cpp \
	   Creation/ConfigurationPopulation.cpp \
	   Creation/BestioleFactory.cpp \
	   Observation/JournalSimulation.cpp

OBJS = $(SRCS:.cpp=.o)

TEST_SRCS = test.cpp \
            Bestioles/Bestiole.cpp \
            CapteursEtAccessoires/DecCamouflage.cpp \
            CapteursEtAccessoires/DecCarapace.cpp \
            CapteursEtAccessoires/DecYeux.cpp \
            CapteursEtAccessoires/DecOreilles.cpp \
	   		CapteursEtAccessoires/DecNageoires.cpp \
            Comportements/Gregaire.cpp \
			Comportements/Peureuse.cpp \
			Comportements/Kamikaze.cpp \
			Comportements/Prevoyante.cpp \
			Comportements/PersonnalitesMultiples.cpp \
            Creation/ConfigurationPopulation.cpp \
            Creation/BestioleFactory.cpp \
            Observation/JournalSimulation.cpp

TEST_OBJS = $(TEST_SRCS:.cpp=.test.o)

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS) -lX11 -lpthread

test: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o test $(TEST_OBJS) -lX11 -lpthread

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.test.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TEST_OBJS) main test