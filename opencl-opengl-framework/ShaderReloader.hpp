//
//  ShaderReloader.hpp
//  OpenGLTest
//
//  Created by Samuel Hall on 27/07/2016.
//
//

#ifndef ShaderReloader_hpp
#define ShaderReloader_hpp

#include <stdio.h>

#include <vector>
#include <thread>
#include <ctime>
#include <boost/filesystem.hpp>

class ShaderReloader
{
private:
    
    std::thread m_monitoring_thread;
    bool m_is_running;
    std::condition_variable m_thread_conditional;
    std::mutex m_thread_mutex;
    std::timed_mutex m_deinit_mutex;
    
    struct File {
        boost::filesystem::path path;
        std::time_t last_write_time;
        std::function<void()> callback;
    };
    
    std::vector<std::shared_ptr<File>> m_watched_files;
    
    void initialize();
    void deinitialize();
        
    void add_files_to_watch(std::function<void ()> callback);

public:
    
    ShaderReloader() {
        
        initialize();
    };
    
    ~ShaderReloader() {
        
        deinitialize();
    };
        
    template<typename ... Args>
	    void add_files_to_watch(std::function<void ()> callback, std::string file_path, Args ... args);
};

template<typename ... Args>
inline void ShaderReloader::add_files_to_watch(std::function<void ()> callback, std::string file_path, Args ... args)
{
    std::shared_ptr<File> file(new File());
    
    file->path = boost::filesystem::path(file_path);
    file->last_write_time = boost::filesystem::last_write_time(file->path);
    file->callback = callback;
    
    m_watched_files.push_back(file);
    
    add_files_to_watch(callback, args...);
}


#endif /* ShaderReloader_hpp */
