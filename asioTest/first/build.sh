g++ -o base_client base_client.cpp -lboost_system -lpthread
g++ -o base_service base_service.cpp -lboost_system -lboost_thread -lpthread

g++ -o async_base_client async_base_client.cpp -lboost_system -lpthread
g++ -o async_base_service async_base_service.cpp -lboost_system -lboost_thread -lpthread
