//
//  ShaderReloader.cpp
//  OpenGLTest
//
//  Created by Samuel Hall on 27/07/2016.
//
//

#include "ShaderReloader.hpp"

#include <iostream>

void ShaderReloader::initialize()
{
    printf("init\n");

    m_is_running = true;
    m_deinit_mutex.lock();
    
    m_monitoring_thread = std::thread( [&] {
                
        while (m_is_running) {
                        
            m_deinit_mutex.try_lock_for(std::chrono::milliseconds(1000));

            for (std::shared_ptr<File> file : m_watched_files) {
                                
                std::time_t last_write_time = boost::filesystem::last_write_time(file->path);
                
                if(last_write_time > file->last_write_time) {
                    
                    file->last_write_time = last_write_time;
                    
                    file->callback();
                }
            }
        }
    });
}

void ShaderReloader::deinitialize()
{
    m_is_running = false;
    
    m_deinit_mutex.unlock();
    
    m_monitoring_thread.join();
}

void ShaderReloader::add_files_to_watch(std::function<void ()> callback)
{
}
