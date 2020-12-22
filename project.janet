(declare-project
  :name "codec"
  :description "A base64 encoding library for janet"
  :author "Sean Walker"
  :license "MIT"
  :url "https://github.com/joy-framework/codec"
  :repo "git+https://github.com/joy-framework/codec")


(declare-native
  :name "codec"
  :source @["codec.c" "base64.c"])
