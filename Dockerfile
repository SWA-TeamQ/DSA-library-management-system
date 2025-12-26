# Multi-stage build for DSA Library Management System
# Build stage
FROM debian:12-slim AS builder

ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
       build-essential cmake \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . /app

# Configure and build in Release
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release \
 && cmake --build build --config Release

# Runtime stage
FROM debian:12-slim AS runtime

# Create non-root user (optional but recommended)
RUN useradd -m runner
WORKDIR /app

# Copy binary from builder. CMake default GNU generator outputs build/lms
COPY --from=builder /app/build/lms /usr/local/bin/lms

# Copy runtime data files if present (optional)
# COPY --from=builder /app/*.txt /app/

USER runner
ENTRYPOINT ["lms"]
