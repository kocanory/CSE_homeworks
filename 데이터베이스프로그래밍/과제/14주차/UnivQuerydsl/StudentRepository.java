package dbp.UnivQuerydsl.repository;

import dbp.UnivQuerydsl.entity.Student; // Student.java 경로
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;

public interface StudentRepository extends JpaRepository<Student, Long> {
    public Optional<Student> findStudentById(Long id);

}

