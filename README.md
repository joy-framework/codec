# codec

encode/decode library for janet

## Install

Add to your `project.janet` file

```clojure
{:dependencies ["https://github.com/joy-framework/codec"]}
```

## Use

```clojure
(import codec)

(= "hello there!" (codec/decode (codec/encode "hello there!")))
```

## HMAC Hex Digests

Codec can also perform sha1 hmac digests on strings

```clojure
(import codec)

(codec/hmac-sha1 "secret token" "hello world")
```

This should be equivalent to the following ruby code:

```ruby
OpenSSL::HMAC.hexdigest(OpenSSL::Digest.new('sha1'), 'secret token', 'hello world')
```
