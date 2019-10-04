(declare-project
  :name "codec"
  :description "A base64 encoding library for janet"
  :author "Sean Walker"
  :license "MIT"
  :dependencies [{:repo "https://github.com/joy-framework/tester" :tag "c14aff3591cb0aed74cba9b54d853cf0bf539ecb"}]
  :url "https://github.com/joy-framework/codec"
  :repo "git+https://github.com/joy-framework/codec")


(declare-native
  :name "codec"
  :source @["codec.c" "base64.c"])
