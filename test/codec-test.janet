(import tester :prefix "" :exit true)
(import build/codec :as codec)

(defsuite "all tests"
  (test "a base64 encoded then decoded string is the same as the original"
    (let [str "original string"]
      (is (= str (codec/decode
                   (codec/encode str))))))

  (test "a base64 encoded string should not end in \\0"
    (let [str "original string"
          enc-str (codec/encode "original string")]
      (is (false? (string/has-suffix? "\0" enc-str)))))

  (test "a base64 decoded string should not end in \\0"
    (let [str "original string"
          decoded-str (codec/decode (codec/encode "original string"))]
      (is (false? (string/has-suffix? "\0" decoded-str)))))

  (test "hmac-sha1"
    (is (= "9f660f792293e132335d86afe5d101f7a856d7b5" (codec/hmac-sha1 "secret token" "hello"))))

  (test "hmac/sha1"
    (is (= "9f660f792293e132335d86afe5d101f7a856d7b5" (codec/hmac/sha1 "secret token" "hello"))))

  (test "md5"
    (is (= "3a315533c0f34762e0c45e3d4e9d525c" (codec/md5 "a string"))))

  (test "sha1"
    (is (= "555d01e6c83266b3e9f92bd811905370caf62770" (codec/sha1 "a string"))))

  (test "sha256"
    (is (= "c0dc86efda0060d4084098a90ec92b3d4aa89d7f7e0fba5424561d21451e1758" (codec/sha256 "a string"))))

  (test "hmac/sha256"
    (is (= "187e6d25aaa29d5de1d2d0b651546aea080458ef13ab94494f7529fc3e15949e" (codec/hmac/sha256 "hello" "hello world")))))
