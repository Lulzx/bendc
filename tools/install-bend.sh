#!/bin/sh
# Installs the official Bend into $BEND_HOME (default ~/.bend), as
# bend-lang.com/install.sh does, but a pinned version: CI uses this, so a
# new Bend release changes what CI tests only when this file changes (the
# weekly CI run tries the latest). `tools/install-bend.sh latest` runs
# bend-lang.com/install.sh itself.
#
# To move the pin: take VER and the four sums from the new release's
# install.sh (curl -fsSL https://bend-lang.com/install.sh | head -25).
set -eu

VER="2.0.26"
SHA_DARWIN_ARM64="a340f4f004860921fb9697e185a05bb1cd4398c74c6192d0b43fc91a36f329ab"
SHA_DARWIN_X64="d904aafdb9999a2c57dd4328d4f86b56b7ba368c302151dab946f7d095f7e3ca"
SHA_LINUX_ARM64="0818627723b4ebde029be7aadb5a66ebb842917aa9b058301bb574b67642d373"
SHA_LINUX_X64="5edcc8e5c12d525655431ab02659ddf88e362aafbe7c7bb7f783a1ffaeb6165c"

if [ "${1:-}" = latest ]; then
  curl -fsSL https://bend-lang.com/install.sh | sh
  exit
fi

case $(uname -s)-$(uname -m) in
  Darwin-arm64) os=darwin arch=arm64 sum=$SHA_DARWIN_ARM64;;
  Darwin-x86_64) os=darwin arch=x64 sum=$SHA_DARWIN_X64;;
  Linux-aarch64|Linux-arm64) os=linux arch=arm64 sum=$SHA_LINUX_ARM64;;
  Linux-x86_64) os=linux arch=x64 sum=$SHA_LINUX_X64;;
  *) echo "install-bend: no Bend build for $(uname -s) $(uname -m)" >&2; exit 1;;
esac

home=${BEND_HOME:-$HOME/.bend}
name="bend-$VER-$os-$arch.tar.gz"
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT
curl --proto '=https' --tlsv1.2 -fsSL -o "$tmp/$name" \
  "https://github.com/bendlang/bend/releases/download/v$VER/$name"
if command -v sha256sum >/dev/null 2>&1; then
  got=$(sha256sum "$tmp/$name" | cut -d' ' -f1)
else
  got=$(shasum -a 256 "$tmp/$name" | cut -d' ' -f1)
fi
[ "$got" = "$sum" ] || { echo "install-bend: $name does not match its sha256" >&2; exit 1; }
tar -xzf "$tmp/$name" -C "$tmp"
mkdir -p "$home/bin"
rm -rf "$home/bend2" "$home/guide"
mv "$tmp/bend/bend2" "$tmp/bend/guide" "$home/"
mv -f "$tmp/bend/bin/bend" "$home/bin/bend"
echo "install-bend: Bend $VER in $home"
