g++ -g -o sync_tcp_client sync_tcp_client.cpp -lboost_system -lboost_thread -lpthread -DBOOST_BIND_GLOBAL_PLACEHOLDERS
g++ -g -o sync_tcp_service sync_tcp_service.cpp -lboost_system -lboost_thread -lpthread -DBOOST_BIND_GLOBAL_PLACEHOLDERS
g++ -g -o async_tcp_client async_tcp_client.cpp -lboost_system -lboost_thread -lpthread -DBOOST_BIND_GLOBAL_PLACEHOLDERS
g++ -g -o async_tcp_service async_tcp_service.cpp -lboost_system -lboost_thread -lpthread -DBOOST_BIND_GLOBAL_PLACEHOLDERS
g++ -g -o sync_udp_client sync_tcp_client.cpp -lboost_system -lboost_thread -lpthread -DBOOST_BIND_GLOBAL_PLACEHOLDERS
g++ -g -o sync_udp_service sync_tcp_service.cpp -lboost_system -lboost_thread -lpthread -DBOOST_BIND_GLOBAL_PLACEHOLDERS
