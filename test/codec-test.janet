(import tester :prefix "" :exit true)
(import build/codec :as codec)

(deftest
  (test "a base64 encoded then decoded string is the same as the original"
    (let [str "original string"]
      (= str (codec/decode
               (codec/encode str)))))

  (test "a base64 encoded string should not end in \\0"
    (let [str "original string"
          enc-str (codec/encode "original string")]
      (false? (string/has-suffix? "\0" enc-str))))

  (test "a base64 decoded string should not end in \\0"
    (let [str "original string"
          decoded-str (codec/decode (codec/encode "original string"))]
      (false? (string/has-suffix? "\0" decoded-str))))

  (test "hmac"
    (= "9f660f792293e132335d86afe5d101f7a856d7b5" (codec/hmac-sha1 "secret token" "hello"))))
