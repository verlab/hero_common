FROM python:3.12-slim-bookworm

ENV DEBIAN_FRONTEND=noninteractive \
    PYTHONUNBUFFERED=1

ARG TORCH_INDEX=https://download.pytorch.org/whl/cpu

RUN apt-get update && apt-get install -y --no-install-recommends \
      git \
      libgl1 \
      libglib2.0-0 \
      libxrender1 \
      libsm6 \
      libxext6 \
      libglfw3 \
    && rm -rf /var/lib/apt/lists/*

RUN pip install --upgrade pip \
 && pip install torch --index-url "${TORCH_INDEX}" \
 && pip install "git+https://github.com/Genesis-Embodied-AI/genesis-world.git"

WORKDIR /hero
COPY hero_description /hero/hero_description
COPY hero_gazebo /hero/hero_gazebo
COPY hero_genesis /hero/hero_genesis

CMD ["python", "/hero/hero_genesis/scripts/genesis_engine.py", "--vis", "--num-robots", "20", "--backend", "cpu", "--no-physics"]
