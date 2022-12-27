g++ -g -o base base_test.cpp -lboost_system -lpthread
g++ -g -o socket_test socket_test.cpp -lboost_system -lpthread
g++ -g -o message_peek_test message_peek_test.cpp -lboost_system -lpthread
g++ -g -o udp_client udp_client.cpp -lboost_system -lpthread
g++ -g -o udp_service udp_service.cpp -lboost_system -lpthread
g++ -g -o async_udp_client async_udp_client.cpp -lboost_system -lboost_thread -lpthread
g++ -g -o async_udp_service async_udp_service.cpp -lboost_system -lpthread
g++ -g -o socket_option_test socket_option_test.cpp -lboost_system -lpthread
g++ -g -o async_new_buffer async_new_buffer.cpp -lboost_system -lboost_thread -lpthread -DBOOST_BIND_GLOBAL_PLACEHOLDERS
g++ -g -o async_shared_buffer async_shared_buffer.cpp -lboost_system -lboost_thread -lpthread -DBOOST_BIND_GLOBAL_PLACEHOLDERS
g++ -g -o async_completion_test async_completion_test.cpp -lboost_system -lboost_thread -lpthread
g++ -g -o async_completion_service async_completion_service.cpp -lboost_system -lboost_thread -lpthread
g++ -g -o read_until_test read_until_test.cpp -lboost_system -lboost_thread -lpthread
g++ -g -o async_persistent_run async_persistent_run.cpp -lboost_system -lboost_thread -lpthread
g++ -g -o post_1 post_1.cpp -lboost_system -lboost_thread -lpthread -DBOOST_BIND_GLOBAL_PLACEHOLDERS
g++ -g -o post_2 post_2.cpp -lboost_system -lboost_thread -lpthread -DBOOST_BIND_GLOBAL_PLACEHOLDERS
