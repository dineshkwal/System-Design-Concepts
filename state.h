// State pattern

#pragma once

#include <memory>
#include <iostream>

namespace dk {
    class MusicPlayerState;
    
    /**
     * MusicPlayer
     **/
    class MusicPlayer
    {
    public:
        enum State
        {
            kPlaying,
            kPaused,
            kStopped
        };
        
        MusicPlayer();
        
        void Play();
        void Pause();
        void Stop();
        void SetState(State state);
        
    private:
        std::unique_ptr<MusicPlayerState> mState;
    };
    
    /**
     * MusicPlayerState
     **/
    class MusicPlayerState
    {
    public:
        virtual void Play(MusicPlayer* player) {}
        virtual void Pause(MusicPlayer* player) {}
        virtual void Stop(MusicPlayer* player) {}
    };
    
    class PlayingState final : public MusicPlayerState
    {
    public:
        void Pause(MusicPlayer* player) override { player->SetState(MusicPlayer::State::kPaused); }
        void Stop(MusicPlayer* player) override { player->SetState(MusicPlayer::State::kStopped); }
    };
    
    class PausedState final : public MusicPlayerState
    {
    public:
        void Play(MusicPlayer* player) override { player->SetState(MusicPlayer::State::kPlaying); }
        void Stop(MusicPlayer* player) override { player->SetState(MusicPlayer::State::kStopped); }
    };
    
    class StoppedState final : public MusicPlayerState
    {
    public:
        void Play(MusicPlayer* player) override { player->SetState(MusicPlayer::State::kPlaying); }
    };
    
    /**
    * MusicPlayer function definition
    **/
    MusicPlayer::MusicPlayer() : mState(std::make_unique<StoppedState>()) { }
    
    void MusicPlayer::Play() { mState->Play(this); }
    
    void MusicPlayer::Pause() { mState->Pause(this); }
    
    void MusicPlayer::Stop() { mState->Stop(this); }
    
    void MusicPlayer::SetState(State state)
    {
        switch (state) {
            case State::kPlaying:
                std::cout << "Changed state to playing\n";
                mState = std::make_unique<PlayingState>();
                break;
                
            case State::kPaused:
                std::cout << "Changed state to paused\n";
                mState = std::make_unique<PausedState>();
                break;
                
            case State::kStopped:
                std::cout << "Changed state to stopped\n";
                mState = std::make_unique<StoppedState>();
                break;
                
            default:
                break;
        }
    }
    
    inline void test_state()
    {
        dk::MusicPlayer player;
        player.Play();
        player.Pause();
        player.Stop();
    }
    
} // namespace dk
