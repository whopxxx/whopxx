```cpp
tmux            # 创建新的 tmux 会话
tmux detach     # 分离当前 tmux 会话，快捷键 Ctrl+B D
tmux ls         # tmux list-session
tmux attach -t <session-name> # Sessions are labeled by numbers by default
tmux kill-session -t <session-name>
```