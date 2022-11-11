g++ -o base_client base_client.cpp -lboost_system -lpthread
g++ -o base_service base_service.cpp -lboost_system -lboost_thread -lpthread

g++ -o async_base_client async_base_client.cpp -lboost_system -lpthread
g++ -o async_base_service async_base_service.cpp -lboost_system -lboost_thread -lpthread

g++ -o signal_test signal_test.cpp -lboost_system -lpthread
g++ -o serial_port_test serial_port_test.cpp -lboost_system -lpthread
g++ -o timer_test timer_test.cpp -lboost_system -lpthread

g++ -o io_service_1 io_service_1.cpp -lboost_system -lpthread
g++ -o io_service_2 io_service_2.cpp -lboost_system -lboost_thread -lpthread
g++ -o io_service_3 io_service_3.cpp -lboost_system -lboost_thread -lpthread
