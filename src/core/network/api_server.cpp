
#include "api_server.hpp"

int api_server(){
  try {
        // Number of threads for the server
        const int num_threads = std::thread::hardware_concurrency();
        
        // The io_context is required for all I/O
        asio::io_context ioc{num_threads};

        // Create and launch the listener
        auto const address = asio::ip::make_address("0.0.0.0");
        auto const port = static_cast<unsigned short>(8080);
        std::make_shared<HTTPListener>(
            ioc,
            tcp::endpoint{address, port})->start();

        // Run the I/O service on multiple threads
        std::vector<std::thread> threads;
        threads.reserve(num_threads - 1);
        for(auto i = num_threads - 1; i > 0; --i)
            threads.emplace_back(
                [&ioc] {
                    ioc.run();
                });
        ioc.run();

        // Wait for all threads to exit
        for(auto& t : threads)
            t.join();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}