g++ -g -o base base_test.cpp -lboost_system -lpthread
g++ -g -o socket_test socket_test.cpp -lboost_system -lpthread
g++ -g -o message_peek_test message_peek_test.cpp -lboost_system -lpthread
g++ -g -o udp_client udp_client.cpp -lboost_system -lpthread
g++ -g -o udp_service udp_service.cpp -lboost_system -lpthread
g++ -g -o async_udp_client async_udp_client.cpp -lboost_system -lboost_thread -lpthread
g++ -g -o async_udp_service async_udp_service.cpp -lboost_system -lpthread
