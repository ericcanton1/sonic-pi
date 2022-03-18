use_bpm 160
use_synth :saw
define :dif do |n1, n2, n3, n4, n5, n6, n7, n8|
  play n1
  sleep 0.5
  play n2
  sleep 0.5
  play n3
  sleep 0.5
  play n4
  sleep 0.5
  play n5
  sleep 0.5
  play n6
  sleep 0.5
  play n7
  sleep 0.5
  play n8
  sleep 0.5
end

live_loop :q do
  with_fx :distortion do
    dif :c2, :e2, :g2, :b2, :c3, :b2, :g2, :e2
    
    dif :c3, :e3, :g3, :b3, :c4, :b3, :g3, :e3
    
    dif :c4, :e4, :g4, :b4, :c5, :b4, :g4, :e4
    
    dif :c5, :e5, :g5, :b5, :c6, :b5, :g5, :e5
  end
end
